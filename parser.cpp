#include "litexp.h"
#include "logic_expr.hpp"
#include "arith_expr.hpp"
#include "operator.hpp"
#include <variant>

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

    private:
        inline void moveView(int n){
            view = view.substr(2);
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

        void parse(string expStr){
            expStr = ExpressionString(expStr);
            variant<ArithExp, LogicExp> parse_val(parse_or_exp(expStr));            
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

        varia

};