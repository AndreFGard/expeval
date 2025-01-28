#pragma once
#include <string>
#include <stdexcept>
#include "litexp.hpp"
#include <string>
using namespace std;

typedef long long int lli;
class ArithExp: public LitExp<ArithExp, lli> {
    public:
        ArithExp(const string &expStr);
        ArithExp(lli expVal);
        ArithExp(char *expStr); // prevent the compiler from casting char * to lli
        inline lli getVal() const override;
        inline void invert();

        string toStr() override;
        variant<bool, long long> apply_operator(const Operator &op, Expression *b) override;
    protected:
        ArithExp *is_compatible(LogicArithExpression *b) override;
    private:
        lli add(LogicArithExpression *b);
        lli sub(LogicArithExpression *b);
        lli mul(LogicArithExpression *b);
        lli div(LogicArithExpression *b);
        bool equal(LogicArithExpression *b) override;
        bool less(LogicArithExpression *b);
        bool greater(LogicArithExpression *b);
        lli val;
        const string expStr;
};

inline lli ArithExp::getVal() const {
    return val;
}

inline void ArithExp::invert(){
    val = -val;
}
