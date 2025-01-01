#include "arith_expr.hpp"
#include "expr.h"

using namespace std;

ArithExpr::ArithExpr(const string &start_expStr, int exp_val): Expr(start_expStr)
{
    val = exp_val;
}

ArithExpr::~ArithExpr()
{
}

//use CRTP to make this reusable across classes without using global functions
inline ArithExpr* ArithExpr::assert_compatible(Expr *b) const {
    if(ArithExpr *casted_b = dynamic_cast<ArithExpr *>(b)){
        return casted_b;
    }
    else{
        throw invalid_argument("Invalid argument: different types");
        return nullptr;
    }
    
}

ArithExpr ArithExpr::operator+(Expr *b) const {
    if (ArithExpr *castedB = assert_compatible(b)){
        return ArithExpr(getExpStr(), val + castedB->getVal());
    }
    return *this;
}

ArithExpr ArithExpr::operator*(Expr *b) const {
    if (ArithExpr *castedB = assert_compatible(b)){
        return ArithExpr(getExpStr(), val * castedB->getVal());
    }
    return *this;
}

const string ArithExpr::toStr() const{
    return to_string(val);

}
const inline lli ArithExpr::getVal() const{
    return val;
}