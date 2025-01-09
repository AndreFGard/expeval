#pragma once
using namespace std;
#include <string>
//every class derived from expr must have an operator+ overload
template <typename T, typename val_type>
class LitExpr
{
private:
    const string expStr;
    const val_type val;
    //     const inline  virtual string toStr() const = 0;
public:
    virtual ~LitExpr();
    virtual *T is_compatible(LitExpr *b);
    virtual inline val_type getVal() const;
    virtual const &val_type add();
    
    // const inline string getExpStr() const { return expStr; }
    // friend ostream &operator<<(ostream &os, const Expr &expr);
};