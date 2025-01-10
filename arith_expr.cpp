#include "litexp.h"
#include "arith_expr.hpp"
#include <stdexcept>

using namespace std;

//may throw
ArithExp::ArithExp(const string &expStr): expStr(expStr){
    val = stoll(expStr);
}

inline lli ArithExp::getVal() const{
    return val;
}

ArithExp *ArithExp::is_compatible(LitExp *b){
    return dynamic_cast<ArithExp *>(b);
}

const lli &ArithExp::add(LitExp *b) {
    if (const ArithExp *castedb = is_compatible(b)){
        val = val + castedb->getVal();
        return val;
    }
    else throw invalid_argument("Invalid argument: different types");

}