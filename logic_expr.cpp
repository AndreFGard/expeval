#include "logic_expr.hpp"
#include <stdexcept>
#include <string>
using namespace std;
using namespace Expeval;


LogicExp::LogicExp(bool expVal): expStr((expVal) ? "true": "false"){
    val = expVal;
}
LogicExp::LogicExp(char *expStr) : LogicExp(string(expStr)) {}

LogicExp::LogicExp(string expStr): expStr(expStr){
    if (expStr == "true") val = true;
    else if (expStr == "false") val = false;
    else throw invalid_argument("Invalid argument: not a boolean value");
}


LogicExp *LogicExp::is_compatible(LogicArithExpression *b){
    return dynamic_cast<LogicExp *>(b);
}

bool LogicExp::or_op (LitExp *b) {
    if (const LogicExp *castedb = is_compatible(b)){
        return (val || castedb->getVal());
    }
    else throw invalid_argument("Invalid argument: different types");
}

bool LogicExp::and_op(LitExp *b){
    if (const LogicExp *castedb = is_compatible(b)){
        return (val && castedb->getVal());
    }
    else throw invalid_argument("Invalid argument: different types");
}

bool LogicExp::equal(LogicArithExpression *b){
    if (const LogicExp *castedb = is_compatible(b)){
        return (val == castedb->getVal());
    }
    else throw invalid_argument("Invalid argument: different types");
}


string LogicExp::toStr() {
    return (val) ? "true" : "false";
}

variant<bool,long long> LogicExp::apply_operator(const Operator &op, LogicArithExpression *b){
    if (LogicExp *castedB = is_compatible(b)){
        switch (op.getType()){
            case OperatorType::Or:
                return or_op(castedB);
            case OperatorType::And:
                return and_op(castedB);
            case OperatorType::Equal:
                return equal(castedB);
            case OperatorType::NotEqual:
                return !equal(castedB);
            default:
                throw invalid_argument("Invalid operator: " + op);
        }
    }
    else throw invalid_argument("Invalid argument: different types");
}