#include "logic_expr.hpp"
#include <stdexcept>
#include <string>
using namespace std;



LogicExp::LogicExp(bool expVal): expStr((expVal) ? "true": "false"){
    val = expVal;
}
LogicExp::LogicExp(char *expStr) : LogicExp(string(expStr)) {}

LogicExp::LogicExp(string expStr): expStr(expStr){
    if (expStr == "true") val = true;
    else if (expStr == "false") val = false;
    else throw invalid_argument("Invalid argument: not a boolean value");
}


//todo make dynamic cast
LogicExp *LogicExp::is_compatible(LogicArithExpression *b){
    return dynamic_cast<LogicExp *>(b);
}

bool LogicExp::or_op (LitExp *b) {
    if (const LogicExp *castedb = is_compatible(b)){
        val = (val || castedb->getVal());
        return val;
    }
    else throw invalid_argument("Invalid argument: different types");
}

bool LogicExp::and_op(LitExp *b){
    if (const LogicExp *castedb = is_compatible(b)){
        val = (val && castedb->getVal());
        return val;
    }
    else throw invalid_argument("Invalid argument: different types");
}

bool LogicExp::equal(LitExp *b){
    if (const LogicExp *castedb = is_compatible(b)){
        val = (val == castedb->getVal());
        return val;
    }
    else throw invalid_argument("Invalid argument: different types");
}


string LogicExp::toStr() {
    return (val) ? "true" : "false";
}
