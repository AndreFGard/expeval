#pragma once
using namespace std;
#include <string>
#include "litexp.hpp"

class LogicExp: public LitExp<LogicExp, bool> {
    public:
        string toStr() override;
        LogicExp (bool val);
        LogicExp (char *expStr); //prevent the compiler from casting char * to bool
        LogicExp (string expStr);
        variant<bool,long long> apply_operator(const Operator &op, LogicArithExpression *b) override;
        inline bool getVal() const;
    protected:
        LogicExp *is_compatible(LogicArithExpression *b) override;
    private:
        bool or_op(LitExp *b);
        bool and_op(LitExp *b);
        bool equal(LogicArithExpression *b) override;
        bool val;
        const string expStr;
    

};

inline bool LogicExp::getVal() const {
    return val;
};

