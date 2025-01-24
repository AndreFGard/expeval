#include "arith_expr.hpp"
#include "logic_expr.hpp"
#include "parser.hpp"
#include "litexp.h"
#include <functional>
#include <stdexcept>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){

    #ifdef DBG
        ifstream inStream("in");
        int operations = INT32_MAX;
    #else
        istream &inStream = cin;
        int operations;
        cin >> operations;
    #endif

    string expstr;
    while (getline(inStream, expstr)){
        try {
            Parser x(expstr);
            cout << x.toStr() << endl;
        } catch(...) {
            cout << "error" << endl;
        }
    }
    
    
}
