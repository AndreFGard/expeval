#include "logic_expr.hpp"
#include "expr.h"
#include <stdexcept>

using namespace std;

LogicExpr::LogicExpr(const string &start_expStr, bool exp_val): Expr(start_expStr)
{
    val = exp_val;
}


//TODO: use CRTP to make this reusable across classes without using global functions
inline LogicExpr* LogicExpr::assert_compatible(Expr *b) const{
    //could also use static cast and or typeid
    if(LogicExpr *casted_b = dynamic_cast<LogicExpr *>(b)){
        return casted_b;
    }
    else{
        throw invalid_argument("Invalid argument: different types");
        return nullptr;
    }
    
}

//TODO: create a custom Exception object for error better syntax error handling
//consider the use of CRTP later
LogicExpr LogicExpr::operator+(Expr *b){
    if (const LogicExpr *casted_b = assert_compatible(b)){
        return LogicExpr(getExpStr(), (val || casted_b->getVal()));
    }
    return *this;

}

const inline string LogicExpr::toStr() const {
    return val ? "true" : "false";
}

const inline bool LogicExpr::getVal() const{
    return val;
}

LogicExpr::~LogicExpr()
{
}
