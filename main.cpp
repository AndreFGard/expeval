#include "arith_expr.hpp"
#include "logic_expr.hpp"
#include "parser.hpp"
#include "litexp.h"
#include <functional>
#include <stdexcept>
#include <iostream>
#include <fstream>
using namespace std;

int main(){

    string expstr;
    while (getline(cin, expstr)){
        try {
            Parser x(expstr);
            cout << x.toStr() << endl;
        } catch(...) {
            cout << "error" << endl;
            return false;
        }
    }
    
    
}
