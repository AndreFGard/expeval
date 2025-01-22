#pragma once
using namespace std;
#include <string>
#include "litexp.h"

class LogicExp: public LitExp<LogicExp, bool> {
    public:
        string toStr() override {
            return (val) ? "true" : "false";
        }
        LogicExp (bool val);
        LogicExp (string expStr);
        bool or_op(LitExp *b) override;
        bool and_op(LitExp *b) override;
        bool equal(LitExp *b) override;
        inline bool getVal() const {
            return val;
        };
        inline void invert(){
            val = !val;
        }
    protected:
        LogicExp *is_compatible(LogicArithExpression *b) override;
    private:
        bool val;
        const string expStr;
    

};
