#pragma once
using namespace std;
#include <string>
#include <stdexcept>
#include "litexp.h"
#include <string>

typedef long long int lli;
class ArithExp: public LitExp<ArithExp, lli> {
    public:
        ArithExp(const string &expStr);
        ArithExp(lli expVal);
        ArithExp(char *expStr); // prevent the compiler from casting char * to lli
        inline lli getVal() const {
            return val;
        }
        inline void invert(){
            val = -val;
        }
        string toStr() override {
            return to_string(val);
        }
        
        lli add(LitExp *b) override;
        lli sub(LitExp *b) override;
        lli mul(LitExp *b) override;
        lli div(LitExp *b) override;
        bool equal(LitExp *b) override;
        bool less(LitExp *b) override;
        bool greater(LitExp *b) override;

    protected:
        ArithExp *is_compatible(LogicArithExpression *b) override;
    private:
        lli val;
        const string expStr;
};
