#include "operator.hpp"
#include <stdexcept>
using namespace std;





Operator::Operator(string_view op){
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
    } else if (op == "!"){
        size = 1;
        type = OperatorType::Not;
    } else {
        throw invalid_argument("Invalid operator: " +string(op));
    }
}