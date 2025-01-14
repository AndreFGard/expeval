#include "operator.hpp"
#include <stdexcept>
using namespace std;





Operator::Operator(string_view op): string(op){
    arity = 2;
    if (op == "+"){
        type = OperatorType::Add;
        size = 1;
    } else if (op == "-"){
        type = OperatorType::Subtract;
        arity = 1;
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
    } else if (op == "!="){
        size = 2;
        type = OperatorType::NotEqual;
    } else if (op == "=="){
        size=2;
        type = OperatorType::Equal;
    } else if (op == "<="){
        size = 2;
        type = OperatorType::LessEqual;
    } else if (op == ">="){
        size = 2;
        type = OperatorType::GreaterEqual;
    } else if (op == "<"){
        size = 1;
        type = OperatorType::Less;
    } else if (op == ">"){
        size = 1;
        type = OperatorType::Greater;
    } else {
        throw invalid_argument("Invalid operator: " +string(op));
    }
}