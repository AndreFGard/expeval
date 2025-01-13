enum class OperatorType {
    Add,
    Subtract,
    Multiply,
    Divide,
    And,
    Or,
    Not
};
#include <stdexcept>
using namespace std;

inline int Operator::getSize(){
    return size;
}

inline OperatorType Operator::getType(){
    return type;
}

Operator::Operator(string_view op){
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