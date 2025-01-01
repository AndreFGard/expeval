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
        inline LogicExpr* assert_compatible(Expr *b) const;
        bool val;
    protected:
        const inline  string toStr() const override;
};

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

ArithExpr::ArithExpr(const string &start_expStr, int exp_val): Expr(start_expStr)
{
    val = exp_val;
}

ArithExpr::~ArithExpr()
{
}

//use CRTP to make this reusable across classes without using global functions
inline ArithExpr* ArithExpr::assert_compatible(Expr *b) const {
    if(ArithExpr *casted_b = dynamic_cast<ArithExpr *>(b)){
        return casted_b;
    }
    else{
        throw invalid_argument("Invalid argument: different types");
        return nullptr;
    }
    
}

ArithExpr ArithExpr::operator+(Expr *b) const {
    if (ArithExpr *castedB = assert_compatible(b)){
        return ArithExpr(getExpStr(), val + castedB->getVal());
    }
    return *this;
}

ArithExpr ArithExpr::operator*(Expr *b) const {
    if (ArithExpr *castedB = assert_compatible(b)){
        return ArithExpr(getExpStr(), val * castedB->getVal());
    }
    return *this;
}

const string ArithExpr::toStr() const{
    return to_string(val);

}
const inline lli ArithExpr::getVal() const{
    return val;
}

LogicExpr::LogicExpr(const string &start_expStr, bool exp_val): Expr(start_expStr)
{
    val = exp_val;
}


//use CRTP to make this reusable across classes without using global functions
inline LogicExpr* LogicExpr::assert_compatible(Expr *b) const{
    if(LogicExpr *casted_b = dynamic_cast<LogicExpr *>(b)){
        return casted_b;
    }
    else{
        throw invalid_argument("Invalid argument: different types");
        return nullptr;
    }
    
}

//TODO: create a custom Exception object for error better syntax error handling
//consider the use of CRTP later
LogicExpr LogicExpr::operator+(Expr *b){
    if (const LogicExpr *casted_b = assert_compatible(b)){
        return LogicExpr(getExpStr(), (val || casted_b->getVal()));
    }
    return *this;

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

    ArithExpr aa (s, 1);
    cout << aa << endl;

    cout << (aa + &aa) << endl;
    //cout << (aa + &la) << endl;


    cout << aa * new ArithExpr(s, 55) << endl;
    cout << aa * &lb << endl;
}
