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
    public:
        virtual variant<opReturnType1,opReturnType2> apply_operator(const Operator &op, Expression *b) = 0;
        virtual string toStr() = 0;
};

using LogicArithExpression = Expression<bool, long long>;

//this seems crtp-like

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

        variant<bool,long long> apply_operator(const Operator &op, LogicArithExpression *b) =0;

    protected:
    virtual bool equal(LogicArithExpression *b) =0;
        virtual Derive* is_compatible(LogicArithExpression *b) = 0;
        LitExp() = default; //prohibiting creation of Litexps, as shown in the documentation
};

