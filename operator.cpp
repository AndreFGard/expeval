#include "operator.hpp"
#include <stdexcept>
using namespace std;

//todo move this to inside Operator
static const unordered_map<string, OperatorType> stringToOp {
        { "+", OperatorType::Add },
        { "- ", OperatorType::Subtract }, //note the whitespace
        { "*", OperatorType::Multiply },
        { "/", OperatorType::Divide },
        { "&&", OperatorType::And },
        { "||", OperatorType::Or },
        { "!=", OperatorType::NotEqual },
        { "==", OperatorType::Equal },
        { "<=", OperatorType::LessEqual },
        { ">=", OperatorType::GreaterEqual },
        { "<", OperatorType::Less },
        { ">", OperatorType::Greater }
};


Operator::Operator(string_view op): string(op){
    arity = 2;
    for (auto [OpStr, OpCode]: stringToOp){
        if (!op.compare(0, OpStr.length(), OpStr)){
            type = OpCode;
            size = OpStr.length();
            if (OpCode == OperatorType::Subtract) arity = 1;
            return;
        }
    }

    throw invalid_argument("Invalid operator: " +string(op));
    
}