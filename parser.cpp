#include "litexp.h"
#include "logic_expr.hpp"
#include "arith_expr.hpp"
#include <variant>
using namespace std;

enum class OperatorType {
    Add,
    Subtract,
    Multiply,
    Divide,
    And,
    Or,
    Not
};

class Operator {
    private:
        OperatorType type;
        int size;
    public:
        Operator(string_view op){
            if (op == "+"){
                type = OperatorType::Add;
                size = 1;
            } else if (op == "-"){
                type = OperatorType::Subtract;
                size =1;
            } else if (op == "*"){
                type = OperatorType::Multiply;
                size =1;
            } else if (op == "/"){
                type = OperatorType::Divide;
                size =1;
            } else if (op == "&&"){
                type = OperatorType::And;
                size =2;
            } else if (op == "||"){
                type = OperatorType::Or;
                size = 2;
            } else if (op == "!"){
                size = 1;
                type = OperatorType::Not;
            } else {
                throw invalid_argument("Invalid operator");
            }
        }
       inline OperatorType getType(){
            return type;
        }
        //returns the size of the string of the operator
        inline int getSize(){
            return size;
        }
};




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
            return Operator(view.substr(0, 2));
            moveView(2);
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