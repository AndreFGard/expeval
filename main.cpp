#include "arith_expr.hpp"
#include "logic_expr.hpp"
#include "parser.cpp"
#include "litexp.h"
#include <functional>
#include <stdexcept>
#include <iostream>
using namespace std;
inline bool assert(bool x){
    if (!x) throw runtime_error("assertion failed");
    return true;
}

inline bool parseAndPrint(string str){
    Parser x(str);
    cout << x.toStr() << endl;
    return true;
}

int main(){
    LogicExp b("false");
    LogicExp a("true");

    assert(a.not_equal(&b));
    assert(a.equal(&a));
    assert(a.or_op(&b));
    assert(a.and_op(&a));

    try {
        b.add(&b);
    }
    catch(runtime_error &e){
        assert(true);
    }
    assert(!b.getVal());
    b.or_op(&b);
    assert(!b.getVal());
    assert(a.getVal());
    b.or_op(&a);
    assert(b.getVal());

    ArithExp c("3");
    ArithExp d("4");
    ArithExp e("7");
    assert(c.less(&d));
    assert(c.less_equal(&d));
    assert(d.greater(&c));
    c.add(&d);
    assert(c.less_equal(&e));
    
    
    //parseAndPrint("true");
    // parseAndPrint("false || true");
    // parseAndPrint("false || (true && true)");
    // parseAndPrint("false || (true && false)");
    // parseAndPrint("1");
    parseAndPrint("1 * 5");
    
    
    
}
