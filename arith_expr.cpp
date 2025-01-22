#include "litexp.h"
#include "arith_expr.hpp"
#include <stdexcept>

using namespace std;

//may throw

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


lli ArithExp::add(LitExp *b) {
    if (const ArithExp *castedb = is_compatible(b)){
        val = val + castedb->getVal();
        return val;
    }
    else throw invalid_argument("Invalid argument: different types");

}

lli ArithExp::sub(LitExp *b) {
    if (const ArithExp *castedb = is_compatible(b)){
        val = val - castedb->getVal();
        return val;
    }
    else throw invalid_argument("Invalid argument: different types");

}

lli ArithExp::mul(LitExp *b){
    if (const ArithExp * castedb = is_compatible(b)){
        val = val * castedb->getVal();
        return val;
    }
    else throw invalid_argument("Invalid argument: different types");
    }

lli ArithExp::div(LitExp *b){
    if (const ArithExp *castedb = is_compatible(b)){
        val = val / castedb->getVal();
        return val;
    }
    else throw invalid_argument("Invalid argument: different types");
}

bool ArithExp::equal(LitExp *b){
    if (const ArithExp *castedb = is_compatible(b)){
        return (val == castedb->getVal());
    }
    else throw invalid_argument("Invalid argument: different types");
}

bool ArithExp::less(LitExp *b){
    if (const ArithExp *castedb = is_compatible(b)){
        return (val < castedb->getVal());
    }
    else throw invalid_argument("Invalid argument: different types");
}

bool ArithExp::greater(LitExp *b){
    if (const ArithExp *castedb = is_compatible(b)){
        return (val > castedb->getVal());
    }
    else throw invalid_argument("Invalid argument: different types");
}

