#include "litexp.h"
#include "logic_expr.hpp"
#include "arith_expr.hpp"
#include "operator.hpp"
#include <variant>
#include <vector>

using namespace std;
//todo fix expressionstring as it shouldnt inherit string
typedef Expression LogicOrArith;
class ExpressionString{
    public:
        ExpressionString(string_view str){
            view = string_view(str);
            stripView();
            original = string(str);
        }
        string getOriginalString(){
            return original;
        }
        
        inline bool startsWith(string prefix){
            return (view.rfind(prefix,0) == 0);
        }
       //todo use operator as an enum or sum 
        Operator parseOperator(){
            auto temp = Operator(view.substr(0, 2));
            moveView(temp.getSize());
            stripView();
            return temp;
        }

        inline void remove_parenthesis(){
            view = view.substr(1, view.size()-2);
            index++;
            stripView();
        }

        inline string_view getView(){
            return view;
        }

    private:
        inline void moveView(int n){
            view = view.substr(2);
            index+=n;
            stripView();
        }

        inline void stripView(){
            while (view[0] == ' '){
                view = view.substr(1);
                index++;
            }
            while (*(view.rbegin()) == ' '){
                view = view.substr(0, view.size()-1);
            }

        }

        string_view view;
        int index =0;
        string original;
};

class Parser{
    public:
        Parser(string originalExpStr) : expStr(originalExpStr){
            parse(originalExpStr);
        }
        Expression *valExpr;

    private:
        int currentToken = 0;

        ExpressionString expStr;
        
        void parse(string str){
            expStr = ExpressionString(str);
            LogicOrArith *parse_val(parse_or_exp(str)); 
            valExpr = parse_val;
        }

        LogicOrArith *parse_or_exp(string &str){
            LogicOrArith *val = (parse_and_exp(str));

            if (expStr.startsWith("||")){
                Operator op = expStr.parseOperator();
                if (op.getType() != OperatorType::Or) 
                    throw runtime_error("Operator parsing not working");
                LogicOrArith *val2 = (parse_and_exp(str));

                //todo  deal with errors
                val->apply_operator(op, val2);
                return val;
            }
            else return val;            
        }

        LogicOrArith *parse_and_exp(string &str){
            LogicOrArith *val = (parse_eq_exp(str));

            if (expStr.startsWith("&&")){
                Operator op = expStr.parseOperator();
                LogicOrArith *val2 = (parse_eq_exp(str));
                val->apply_operator(op, val2);
                return val;
            }
            return val;
        }
        
        //todo check compatibility here, to more quickly know if there
        //is a mismatch between subexpr types
        LogicOrArith *parse_eq_exp(string &str){
            LogicOrArith *val = (parse_rel_exp(str));
            if (expStr.startsWith("==")){                
                Operator op = expStr.parseOperator();
                LogicOrArith *val2 = (parse_rel_exp(str));
                //todo fix this: is this correct? it should get
                //any value, no matter what type it is.
                val->apply_operator(op, val2);
                return val;
            }
            else if (expStr.startsWith("!=")){
                Operator op = expStr.parseOperator();
                LogicOrArith *val2 = (parse_rel_exp(str));
                val->apply_operator(op, val2);
                return val;   
            }
            return val;
        }

        LogicOrArith *parse_rel_exp(string &str){
            LogicOrArith *val = (parse_add_exp(str));

            vector<string> opStrs = {
                "<",">","<=",">="
            };

            for (auto &opStr: opStrs){
                if (!expStr.startsWith(opStr)) continue;
                Operator op = expStr.parseOperator();
                LogicOrArith *val2 = (parse_add_exp(str));
                val->apply_operator(op, val2);
                return val;  
            }
            return val;
        }

        LogicOrArith *parse_add_exp(string &str){
            LogicOrArith *val = (parse_mul_exp(str));
            vector<string> opStrs = {"-", "+"};
            for (auto &opStr: opStrs){
                if (!expStr.startsWith(opStr)) continue;
                Operator op = expStr.parseOperator();
                LogicOrArith *val2 = (parse_mul_exp(str));
                val->apply_operator(op, val2);
                return val;  
            }
            return val;
        }

        LogicOrArith *parse_mul_exp(string &str){
            LogicOrArith *val = (parse_unary_exp(str));
            vector< string> opStrs = {"*", "/"};
            for (auto &opStr: opStrs){
                if (!expStr.startsWith(opStr)) continue;
                Operator op = expStr.parseOperator();
                LogicOrArith *val2 = (parse_unary_exp(str));
                val->apply_operator(op, val2); 
                return val;  
            }
            return val;
        }
       
        LogicOrArith *parse_unary_exp(string &str){
            if (expStr.startsWith("-")){
                Operator op = expStr.parseOperator();
                //todo apply the minuss operator with an unary operator function;
                LogicOrArith *val = (parse_unary_exp(str));
                return val;
            }
            else if (expStr.startsWith("(")){
                //todo figure how to deal with recursion in this case
                expStr.remove_parenthesis();
                return parse_or_exp(str);
            }
            else return parse_lit(str); 

        }


        LogicOrArith *parse_lit(string &str){
            //todo figure how to tell if something is an int or a string
            string cur_str = string(expStr.getView());
            try{
                ArithExp* temp = new ArithExp(cur_str);
                return temp;
            } catch (invalid_argument &_){
                LogicExp* temp= new LogicExp(cur_str);
                return temp;
            }

        }

};