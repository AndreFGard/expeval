#pragma once
using namespace std;
#include <string>
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