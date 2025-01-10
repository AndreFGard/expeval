#pragma once
using namespace std;
#include <string>
#include "litexp.h"

class LogicExp: public LitExp<LogicExp, bool> {
    public:
        LogicExp (string &expStr);
        const bool &add (LitExp *b) override;
        inline bool getVal() const;
    protected:
        LogicExp *is_compatible(LitExp *b) override;
    private:
        bool val;
        const string expStr;
    

};
