#include "litexp.h"
#include "logic_expr.hpp"
#include "arith_expr.hpp"
#include "operator.hpp"
#include <variant>
#include <vector>

using namespace std;
//todo fix expressionstring as it shouldnt inherit string
class ExpressionString: public string{
    public:
        ExpressionString(string_view str): string(str){
            view = string_view(str);
        }
        string getOriginalString(){
            return *this;
        }
        
        inline bool startsWith(string prefix){
            return (view.rfind(prefix,0) == 0);
        }
       //todo use operator as an enum or sum 
        Operator parseOperator(){
            auto temp = Operator(view.substr(0, 2));
            moveView(temp.getSize());
            return temp;
        }

        inline void remove_parenthesis(){
            view = view.substr(1, view.size()-2);
            index++;
        }

    private:
        inline void moveView(int n){
            view = view.substr(2);
            index+=n;
        }
        string_view view;
        int index =0;
};

class Parser{
    public:
        Parser() : expStr("")
        {
        }

    private:
        int currentToken = 0;

        ExpressionString expStr;

        void parse(string str){
            expStr = ExpressionString(str);
            variant<ArithExp, LogicExp> parse_val(parse_or_exp(str));            
        }

        variant<ArithExp, LogicExp> parse_or_exp(string &str){
            variant<ArithExp, LogicExp> val(parse_and_exp(str));

            if (expStr.startsWith("||")){
                Operator op = expStr.parseOperator();
                if (op.getType() != OperatorType::Or) 
                    throw runtime_error("Operator parsing not working");
                variant<ArithExp, LogicExp> val2(parse_and_exp(str));

                //todo  deal with errors
                variant<ArithExp, LogicExp> temp = get<LogicExp>(val).apply_operator(op, &get<LogicExp>(val2));
                return temp;
            }
            else return val;            
        }

        variant<ArithExp, LogicExp> parse_and_exp(string &str){
            variant<ArithExp, LogicExp> val(parse_eq_exp(str));

            if (expStr.startsWith("&&")){
                Operator op = expStr.parseOperator();
                variant<ArithExp, LogicExp> val2(parse_eq_exp(str));
                variant<ArithExp, LogicExp> temp = get<LogicExp>(val).apply_operator(op, &get<LogicExp>(val2));
                return temp;
            }
            return val;
        }
        
        //todo check compatibility here, to more quickly know if there
        //is a mismatch between subexpr types
        variant<ArithExp, LogicExp> parse_eq_exp(string &str){
            variant<ArithExp, LogicExp> val(parse_rel_exp(str));
            if (expStr.startsWith("==")){                
                Operator op = expStr.parseOperator();
                variant<ArithExp, LogicExp> val2(parse_rel_exp(str));
                variant<ArithExp, LogicExp> temp = get<ArithExp>(val).apply_operator(op, &get<ArithExp>(val2));
                return temp;
            }
            else if (expStr.startsWith("!=")){
                Operator op = expStr.parseOperator();
                variant<ArithExp, LogicExp> val2(parse_rel_exp(str));
                variant<ArithExp, LogicExp> temp = get<ArithExp>(val).apply_operator(op, &get<ArithExp>(val2));
                return temp;   
            }
            return val;
        }


        variant<ArithExp, LogicExp> parse_eq_exp(string &str){
            variant<ArithExp, LogicExp> val(parse_rel_exp(str));
            if (expStr.startsWith("==")){                
                Operator op = expStr.parseOperator();
                variant<ArithExp, LogicExp> val2(parse_rel_exp(str));
                //todo fix this: is this correct? it should get
                //any value, no matter what type it is.
                variant<ArithExp, LogicExp> temp = get<ArithExp>(val).apply_operator(op, &get<ArithExp>(val2));
                return temp;
            }
            else if (expStr.startsWith("!=")){
                Operator op = expStr.parseOperator();
                variant<ArithExp, LogicExp> val2(parse_rel_exp(str));
                variant<ArithExp, LogicExp> temp = get<ArithExp>(val).apply_operator(op, &get<ArithExp>(val2));
                return temp;   
            }
            return val;
        }

        variant<ArithExp, LogicExp> parse_rel_exp(string &str){
            variant<ArithExp, LogicExp> val(parse_add_exp(str));

            const vector<const string> opStrs = {
                "<",">","<=",">="
            };

            for (auto &opStr: opStrs){
                if (!expStr.startsWith(opStr)) continue;
                Operator op = expStr.parseOperator();
                variant<ArithExp, LogicExp> val2(parse_add_exp(str));
                variant<ArithExp, LogicExp> temp = get<ArithExp>(val).apply_operator(op, &get<ArithExp>(val2));
                return temp;  
            }
            return val;
        }

        variant<ArithExp, LogicExp> parse_add_exp(string &str){
            variant<ArithExp, LogicExp> val(parse_mul_exp(str));
            const vector<const string> opStrs = {"-", "+"};
            for (auto &opStr: opStrs){
                if (!expStr.startsWith(opStr)) continue;
                Operator op = expStr.parseOperator();
                variant<ArithExp, LogicExp> val2(parse_mul_exp(str));
                variant<ArithExp, LogicExp> temp = get<ArithExp>(val).apply_operator(op, &get<ArithExp>(val2));
                return temp;  
            }
        }

        variant<ArithExp, LogicExp> parse_mul_exp(string &str){
            variant<ArithExp, LogicExp> val(parse_unary_exp(str));
            const vector<const string> opStrs = {"*", "/"};
            for (auto &opStr: opStrs){
                if (!expStr.startsWith(opStr)) continue;
                Operator op = expStr.parseOperator();
                variant<ArithExp, LogicExp> val2(parse_unary_exp(str));
                variant<ArithExp, LogicExp> temp = get<ArithExp>(val).apply_operator(op, &get<ArithExp>(val2));
                return temp;  
            }
        }
       
        variant<ArithExp, LogicExp> parse_unary_exp(string &str){
            if (expStr.startsWith("-")){
                Operator op = expStr.parseOperator();
                //todo apply the minuss operator with an unary operator function;
                variant<ArithExp, LogicExp> val(parse_unary_exp(str));
                return val;
            }
            variant<ArithExp, LogicExp> val(parse_unary_exp(str)); 
            return val;
        }

        variant<ArithExp, LogicExp> parse_unary_exp(string &str){
            if (expStr.startsWith("(")){
                expStr.remove_parenthesis();
                //todo figure how to deal with recursion in this case
            }
            return parse_lit(str);

        }
        variant<ArithExp, LogicExp> parse_lit(string &str){
            //todo figure how to tell if something is an int or a string
            
        }

};