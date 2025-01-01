#include <iostream>
//#include "expr.h"
using namespace std;

//every class derived from expr must have an operator+ overload
class Expr
{
private:
    const string expStr;
protected:
    const inline  virtual string toStr() const = 0;
public:
    Expr(const string &start_expStr);
    virtual ~Expr();
    const inline string getExpStr() const { return expStr; }
    friend ostream &operator<<(ostream &os, const Expr &expr);
};
//init list as to allow const attributes
Expr::Expr(const string &start_expStr) : expStr(start_expStr)
{
}

Expr::~Expr()
{
}

// Overload the ostream << operator  using the friended function
ostream &operator<<(ostream &os, const Expr &expr)
{
    os << expr.toStr();
    return os;
}


class LogicExpr: public Expr{
    public:
        LogicExpr(const string &start_expStr, bool val);
        virtual ~LogicExpr();
        LogicExpr operator+(Expr *b);
        const inline bool getVal() const;
    private:
        bool val;
    protected:
        const inline  string toStr() const override;
};

LogicExpr::LogicExpr(const string &start_expStr, bool exp_val): Expr(start_expStr)
{
    val = exp_val;
}

LogicExpr LogicExpr::operator+(Expr *b){
    if (const LogicExpr *casted_b = dynamic_cast<LogicExpr *>(b)){
        return LogicExpr(getExpStr(), (val || casted_b->getVal()));
    }
    else{
        throw invalid_argument("Invalid argument: different types");
        return *this;
    }

}

const inline string LogicExpr::toStr() const {
    return val ? "true" : "false";
}

const inline bool LogicExpr::getVal() const{
    return val;
}

LogicExpr::~LogicExpr()
{
}


int main(){

    string s = "eae";
    LogicExpr la (s, false);
    LogicExpr lb (s, true);
    cout << (la + &lb) << endl;
    cout << la << endl;
    cout << lb << endl;

}
