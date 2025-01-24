#include "arith_expr.hpp"
#include "logic_expr.hpp"
#include "parser.hpp"
#include "litexp.hpp"
#include <functional>
#include <stdexcept>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]){


    string expstr;
    #ifdef DBG
        ifstream inStream; //auto closed
        inStream.open("in");
        if (!inStream.is_open()) {
            cerr << "couldnt open test file in" << endl;
            cerr << "please dont use -DDBG if you dont have a test file" << endl;
            return 1;
        }
        int noperations = INT32_MAX;
    #else
        istream &inStream = cin;
        int noperations;
        cin >> noperations;
        getline(cin, expstr);
        // remove leftover newline
    #endif
    
    int ops = 0;
    while (( ops++ < noperations) && getline(inStream, expstr)){
        try {
            Parser x(expstr);
            cout << x.toStr() << endl;
        } catch(...) {
            cout << "error" << endl;
        }
    }
    
    
}
