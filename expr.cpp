#include <iostream>
//#include "expr.h"
using namespace std;

//every class derived from expr must have an operator+ overload
class Expr
{
private:
    const string expStr;
public:
    Expr(const string &start_expStr);
    virtual ~Expr();
    const inline string getExpStr() const { return expStr; }
};
//init list as to allow const attributes
Expr::Expr(const string &start_expStr) : expStr(start_expStr)
{
}

Expr::~Expr()
{
}


class LogicExpr: public Expr{
    public:
        LogicExpr(const string &start_expStr, bool val);
        virtual ~LogicExpr();
        LogicExpr operator+(Expr *b);
        const inline bool getVal() const;
    private:
        bool val;

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

const inline bool LogicExpr::getVal() const{
    return val;
}

LogicExpr::~LogicExpr()
{
}


class ArithExpr: public Expr{
    public:
        ArithExpr(const string &start_expStr, int val);
        virtual ~ArithExpr();
        ArithExpr operator+(Expr *b);
        const inline int getVal() const;
    private:
        int val;

};

ArithExpr::ArithExpr(const string &start_expStr, int exp_val): Expr(start_expStr)
{
    val = exp_val;
}

ArithExpr ArithExpr::operator+(Expr *b){
    if (const ArithExpr *casted_b = dynamic_cast<ArithExpr *>(b)){
        return ArithExpr(getExpStr(), (val + casted_b->getVal()));
    }
    else{
        throw invalid_argument("Invalid argument: different types");
        return *this;
    }

}

const inline int ArithExpr::getVal() const{
    return val;
}

ArithExpr::~ArithExpr()
{
}


int main(){

    string s = "eae";
    LogicExpr la (s, false);
    LogicExpr lb (s, true);

    ArithExpr aa(s, 10);
    ArithExpr ab(s, 20);

    cout << (la + &lb).getVal() << " is the val of la + lb\n";
    cout << (aa + &ab).getVal() << " is the val of aa + ab\n";
    cout << (la + &ab).getVal() << " is the val of aa + ab\n";

}
