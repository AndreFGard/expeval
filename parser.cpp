#include "litexp.h"
#include "logic_expr.hpp"
#include "arith_expr.hpp"
#include "operator.hpp"
#include <variant>
#include <vector>

using namespace std;
//todo fix expressionstring as it shouldnt inherit string
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

        string getSubExpressionString(){
            int firstOpening = 0, lastClosing =-1;
            for (int i=0;i<view.length();i++){
                if (view[i] == ')') lastClosing = i;
            }
            string temp = string(view).substr(1+1, lastClosing-firstOpening-1-1-1); //+1 because of spaces
            moveView(lastClosing+1);
            return temp;
        }

        inline string_view getView(){
            return view;
        }

        variant<bool, lli> parseLit(){
            if (startsWith("true")){
                moveView(4);
                return true;
            }
            else if (startsWith("false")){
                moveView(5);
                return false;
            }
            else {
                string numS;
                int stIdx = 0;
                int negative = 1;
                if(view[0] == '-'){
                    negative = -1;
                    moveView(1);
                }

                while (isdigit(view[stIdx])){
                    numS += view[stIdx];
                    //moveView(1);
                    //todo perhaps i could deal with subtraction right here
                    stIdx++;
                }
                moveView(stIdx);
                return negative *stoll(numS);

            }
        }

    private:
        inline void moveView(int n){
            view = view.substr(n);
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
        LogicArithExpression *valExpr;

        string toStr(){
            return valExpr->toStr();
        }

    private:
        int currentToken = 0;

        ExpressionString expStr;
        
        void parse(string str){
            expStr = ExpressionString(str);
            LogicArithExpression *parse_val(parse_or_exp(str)); 
            valExpr = parse_val;
        }

        LogicArithExpression *parse_or_exp(string &str){
            LogicArithExpression *val = (parse_and_exp(str));

            if (expStr.startsWith("||")){
                Operator op = expStr.parseOperator();
                if (op.getType() != OperatorType::Or) 
                    throw runtime_error("Operator parsing not working");
                LogicArithExpression *val2 = (parse_and_exp(str));

                //todo  deal with errors
                //free val
                LogicArithExpression *nval = new LogicExp(get<bool>(val->apply_operator(op, val2)));
                return nval;
            }
            else return val;            
        }

        LogicArithExpression *parse_and_exp(string &str){
            LogicArithExpression *val = (parse_eq_exp(str));

            if (expStr.startsWith("&&")){
                Operator op = expStr.parseOperator();
                LogicArithExpression *val2 = (parse_eq_exp(str));

                LogicArithExpression *nval = new LogicExp(get<bool>(val->apply_operator(op, val2)));
                return nval;
            }
            return val;
        }
        
        //todo check compatibility here, to more quickly know if there
        //is a mismatch between subexpr types
        LogicArithExpression *parse_eq_exp(string &str){
            LogicArithExpression *val = (parse_rel_exp(str));
            if (expStr.startsWith("==")){                
                Operator op = expStr.parseOperator();
                LogicArithExpression *val2 = (parse_rel_exp(str));
                //todo fix this: is this correct? it should get
                //any value, no matter what type it is.
                LogicArithExpression *nval = new LogicExp(get<bool>(val->apply_operator(op, val2)));
                return nval;
            }
            else if (expStr.startsWith("!=")){
                Operator op = expStr.parseOperator();
                LogicArithExpression *val2 = (parse_rel_exp(str));
                LogicArithExpression *nval = new LogicExp(get<bool>(val->apply_operator(op, val2)));
                return nval;
            }
            return val;
        }

        LogicArithExpression *parse_rel_exp(string &str){
            LogicArithExpression *val = (parse_add_exp(str));

            vector<string> opStrs = {
                "<",">","<=",">="
            };

            for (auto &opStr: opStrs){
                if (!expStr.startsWith(opStr)) continue;
                Operator op = expStr.parseOperator();
                LogicArithExpression *val2 = (parse_add_exp(str));
                LogicArithExpression *nval = new LogicExp(get<bool>(val->apply_operator(op, val2)));
                return nval;
            }
            return val;
        }

        LogicArithExpression *parse_add_exp(string &str){
            LogicArithExpression *val = (parse_mul_exp(str));
            vector<string> opStrs = {"- ", "+"};
            for (auto &opStr: opStrs){
                if (!expStr.startsWith(opStr)) continue;
                Operator op = expStr.parseOperator();
                LogicArithExpression *val2 = (parse_mul_exp(str));
                val->apply_operator(op, val2);
                return val;  
            }
            return val;
        }

        LogicArithExpression *parse_mul_exp(string &str){
            LogicArithExpression *val = (parse_unary_exp(str));
            vector< string> opStrs = {"*", "/"};
            for (auto &opStr: opStrs){
                if (!expStr.startsWith(opStr)) continue;
                Operator op = expStr.parseOperator();
                LogicArithExpression *val2 = (parse_unary_exp(str));
                val->apply_operator(op, val2); 
                return val;  
            }
            return val;
        }
       
        LogicArithExpression *parse_unary_exp(string &str){
            if (expStr.startsWith("- ")){
                Operator op = expStr.parseOperator();
                //todo apply the minuss operator with an unary operator function;
                LogicArithExpression *val = (parse_unary_exp(str));
                val->invert();
                return val;
            }
            LogicArithExpression *val = parse_primary_exp(str);
            return val;
        }

        LogicArithExpression *parse_primary_exp(string &str){
            if (expStr.startsWith("(")){
                string subexpStr = expStr.getSubExpressionString();
                Parser *subparser = new Parser(subexpStr);
                LogicArithExpression *subexpResult = subparser->valExpr;
                return subexpResult;
            }
            LogicArithExpression *val = parse_lit(str);
            return val;
        }


        LogicArithExpression *parse_lit(string &str){
            variant<bool,lli> lit = expStr.parseLit();
            if (bool *b = get_if<bool>(&lit)){
                return new LogicExp((*b) ? "true" : "false");
            }
            else if (lli *i = get_if<lli>(&lit)){
                return new ArithExp(to_string(*i));
            }
            else throw runtime_error("Invalid literal");
        }

};