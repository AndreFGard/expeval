#pragma once
using namespace std;
#include <string>
#include <stdexcept>
#include "expr.h"

typedef long long int lli;
class ArithExpr: public Expr {
    public:
        ArithExpr(const string &start_expStr, int val);
        virtual ~ArithExpr();
        ArithExpr operator+(Expr *b) const;
        const inline lli getVal() const;
        ArithExpr operator*(Expr *b) const;
    private:
        inline ArithExpr* assert_compatible(Expr *b) const;
        int val;
    protected:
        const inline  string toStr() const override;
};
