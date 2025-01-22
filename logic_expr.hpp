#pragma once
using namespace std;
#include <string>
#include "litexp.h"

class LogicExp: public LitExp<LogicExp, bool> {
    public:
        string toStr() override;
        LogicExp (bool val);
        LogicExp (char *expStr); //prevent the compiler from casting char * to bool
        LogicExp (string expStr);
        bool or_op(LitExp *b) override;
        bool and_op(LitExp *b) override;
        bool equal(LitExp *b) override;
        inline bool getVal() const;
        inline void invert();
    protected:
        LogicExp *is_compatible(LogicArithExpression *b) override;
    private:
        bool val;
        const string expStr;
    

};

inline bool LogicExp::getVal() const {
    return val;
};

inline void LogicExp::invert(){
    val = !val;
}