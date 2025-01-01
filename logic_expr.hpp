#pragma once
using namespace std;
#include <string>
#include "expr.h"

class LogicExpr: public Expr{
    public:
        LogicExpr(const string &start_expStr, bool val);
        virtual ~LogicExpr();
        LogicExpr operator+(Expr *b);
        const inline bool getVal() const;
    private:
        inline LogicExpr* assert_compatible(Expr *b) const;
        bool val;
    protected:
        const inline  string toStr() const override;
};
