#include "litexp.hpp"
#include "arith_expr.hpp"
#include <stdexcept>

using namespace std;
using namespace Expeval;

string ArithExp::toStr(){
    return to_string(val);
}

ArithExp::ArithExp(const lli expVal): expStr(to_string(expVal)){
    val = expVal;
}


ArithExp::ArithExp(const string &expStr): expStr(expStr){
    val = stoll(expStr);
}

ArithExp::ArithExp(char *expStr): ArithExp(string(expStr)) {}


ArithExp *ArithExp::is_compatible(LogicArithExpression *b){
    return dynamic_cast<ArithExp *>(b);
}


lli ArithExp::add(LogicArithExpression *b) {
    if (const ArithExp *castedb = is_compatible(b)){
        return val + castedb->getVal();
    }
    else throw invalid_argument("Invalid argument: different types");

}

lli ArithExp::sub(LogicArithExpression *b) {
    if (const ArithExp *castedb = is_compatible(b)){
        return val - castedb->getVal();
    }
    else throw invalid_argument("Invalid argument: different types");

}

lli ArithExp::mul(LogicArithExpression *b){
    if (const ArithExp * castedb = is_compatible(b)){
        return val * castedb->getVal();
    }
    else throw invalid_argument("Invalid argument: different types");
    }

lli ArithExp::div(LogicArithExpression *b){
    if (const ArithExp *castedb = is_compatible(b)){
        if (castedb->getVal() == 0) {
            throw invalid_argument("Division by zero");
        }
        return val / castedb->getVal();
    }
    else throw invalid_argument("Invalid argument: different types");
}

bool ArithExp::equal(LogicArithExpression *b){
    if (const ArithExp *castedb = is_compatible(b)){
        return (val == castedb->getVal());
    }
    else throw invalid_argument("Invalid argument: different types");
}

bool ArithExp::less(LogicArithExpression *b){
    if (const ArithExp *castedb = is_compatible(b)){
        return (val < castedb->getVal());
    }
    else throw invalid_argument("Invalid argument: different types");
}

bool ArithExp::greater(LogicArithExpression *b){
    if (const ArithExp *castedb = is_compatible(b)){
        return (val > castedb->getVal());
    }
    else throw invalid_argument("Invalid argument: different types");
}


variant<bool,long long> ArithExp::apply_operator(const Operator &op, LogicArithExpression *b) {
    OperatorType opType = op.getType();
    if (ArithExp *castedB = is_compatible(b)){
        switch (opType) {
            case OperatorType::Add:
                return add(castedB);
            case OperatorType::Multiply:
                return mul(castedB);
            case OperatorType::Divide:
                return div(castedB);
            case OperatorType::Equal:
                return equal(castedB);
            case OperatorType::NotEqual:
                return !equal(castedB);
            case OperatorType::GreaterEqual:
                return (equal(castedB) || greater(castedB));
            case OperatorType::LessEqual:
                return !greater(castedB);
            case OperatorType::Greater:
                return greater(castedB);
            case OperatorType::Less:
                return (this->less(castedB));
            case OperatorType::Subtract:
                return (sub(castedB));
            default:
                throw runtime_error("Unimplemented operator: " + op);
        }
    }
    else throw invalid_argument("Incompatible types");
}