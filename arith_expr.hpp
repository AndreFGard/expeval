#pragma once
using namespace std;
#include <string>
#include <stdexcept>
#include "litexp.h"

typedef long long int lli;class ArithExp: public LitExp<ArithExp, lli> {
    public:
        ArithExp(const string &expStr);
        lli add(LitExp *b) override;
        inline lli getVal() const;
    protected:
        ArithExp *is_compatible(LitExp *b) override;
    private:
        lli val;
        const string expStr;
};
