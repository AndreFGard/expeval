#include "litexp.h"
#include "logic_expr.hpp"
#include "arith_expr.hpp"
#include <variant>
using namespace std;

class ExpressionString: public string{
    public:
        ExpressionString(string_view str): string(str){
            view = string_view(str);
        }
        string getOriginalString(){
            return *this;
        }
        
        bool startsWith(string prefix){
            return (view.rfind(prefix,0) == 0);
        }
       //todo use operator as an enum or sum 
        Operator parseOperator(){
            if ()
        }
    private:
        string_view view;
        int index =0;

class Operator{
    public:
    //todo add errors
        Operator(string_view op): op(op){
            if (op)
        }
    private:
        string_view op;
}


class Parser{
    public:
        Parser()
        {

        }


    private:
        int currentToken = 0;
        string_view curview;

        bool starts_with(string prefix){
            return( curview.rfind(prefix,0) == 0);
        }

        void parse(string expStr){
            variant<ArithExp, LogicExp> parse_val(parse_or_exp(expStr));            
        }

        variant<ArithExp, LogicExp> parse_or_exp(string expStr){
            variant<ArithExp, LogicExp> 
                val(parse_and_exp(expStr));

            if (starts_with(string("||"))){
                
            }

            return val;
            

        }

};