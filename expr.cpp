#include <iostream>
#include "expr.h"
using namespace std;


//init list as to allow const attributes
Expr::Expr(const string &start_expStr) : expStr(start_expStr)
{
}

Expr::~Expr()
{
}


ostream &operator<<(ostream &os, const Expr &expr)
{
    os << expr.toStr();
    return os;
}


