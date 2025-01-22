#pragma once
using namespace std;
#include <string>
#include "operator.hpp"
#include <stdexcept>
#include <variant>

template <typename opReturnType1, typename opReturnType2>
class Expression {
    protected:
        Expression() = default;
        bool invert_val = false;
    public:
        virtual variant<opReturnType1,opReturnType2> apply_operator(Operator op, Expression *b) = 0;
        virtual string toStr() = 0;
        virtual void invert() = 0;

};

using LogicArithExpression = Expression<bool, long long>;

//todo: static assert to force the implementation of methods
//this is crtp like, but also creates vtables as runtime polymorphism makes the code smaller

//todo perhaps use std::visit + std;:alternatives to do fancier polymorphism and use overloading instead of 
//dynamic cast
template <typename Derive, typename val_type>
class LitExp: public LogicArithExpression
{
    private:
        const string expStr;
        val_type val;
        //     const inline  virtual string toStr() const = 0;
    public:
        virtual string toStr() override {
            return string();
        };

        virtual inline val_type getVal() const = 0;
        //Add, Subtract, Multiply, Divide, And, Or, NotEqual, Equal, LessEqual, GreaterEqual, Less, Greater
        
        virtual bool equal(LogicArithExpression *b) =0;

        variant<bool,long long> apply_operator(Operator op, Expression *b) =0;
        
        //apply binary operator

        // const inline string getExpStr() const { return expStr; }
        // friend ostream &operator<<(ostream &os, const Expr &expr);
    protected:
        virtual Derive* is_compatible(Expression *b) = 0;
        LitExp() = default; //prohibiting creation of Litexps, as shown in the documentation
};

