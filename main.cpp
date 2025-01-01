

#include <iostream>
#include "expr.h" 
#include "logic_expr.hpp"
#include "arith_expr.hpp"
int main(){

    string s = "eae";
    LogicExpr la (s, false);
    LogicExpr lb (s, true);
    cout << (la + &lb) << endl;
    cout << la << endl;
    cout << lb << endl;

    ArithExpr aa (s, 1);
    cout << aa << endl;

    cout << (aa + &aa) << endl;
    //cout << (aa + &la) << endl;


    cout << aa * new ArithExpr(s, 55) << endl;
    cout << aa * &lb << endl;
}
