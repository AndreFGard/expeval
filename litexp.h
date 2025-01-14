#pragma once
using namespace std;
#include <string>
#include "operator.hpp"
#include <stdexcept>

//todo: static assert to force the implementation of methods
//this is crtp like, but also creates vtables as runtime polymorphism makes the code smaller

//todo perhaps use std::visit + std;:alternatives to do fancier polymorphism and use overloading instead of 
//dynamic cast
template <typename Derive, typename val_type>
class LitExp
{
    private:
        const string expStr;
        val_type val;
        //     const inline  virtual string toStr() const = 0;
    public:
        virtual inline val_type getVal() const = 0;
        //Add, Subtract, Multiply, Divide, And, Or, NotEqual, Equal, LessEqual, GreaterEqual, Less, Greater
        
        virtual val_type add(LitExp *b) {
            throw runtime_error("add() not implemented");
        }
        virtual val_type sub(LitExp *b) {
            throw runtime_error("sub() not implemented");
        }
        virtual val_type mul(LitExp *b) {
            throw runtime_error("mul() not implemented");
        }
        virtual val_type div(LitExp *b) {
            throw runtime_error("div() not implemented");
        }
        virtual bool and_op(LitExp *b) {
            throw runtime_error("and_op() not implemented");
        }
        virtual bool or_op(LitExp *b) {
            throw runtime_error("or_op() not implemented");
        }
        virtual bool equal(LitExp *b) {
            throw runtime_error("equal() not implemented");
        }
        virtual bool less(LitExp *b) {
            throw runtime_error("less() not implemented");
        }
        virtual bool greater(LitExp *b) {
            throw runtime_error("greater() not implemented");
        }

        virtual bool less_equal(LitExp *b);
        virtual bool greater_equal(LitExp *b);
        virtual bool not_equal(LitExp *b);


        
        //apply binary operator
        Derive apply_operator(Operator op, LitExp *b);

        // const inline string getExpStr() const { return expStr; }
        // friend ostream &operator<<(ostream &os, const Expr &expr);
    protected:
        virtual Derive* is_compatible(LitExp *b) = 0;
        LitExp() = default; //prohibiting creation of Litexps, as shown in the documentation
};


template <typename Derive, typename val_type>
bool LitExp<Derive, val_type>::less_equal(LitExp<Derive, val_type> *b) {
    return !greater(b);
}

template <typename Derive, typename val_type>
bool LitExp<Derive, val_type>::greater_equal(LitExp<Derive, val_type> *b) {
    return (!less(b));
}

template <typename Derive, typename val_type>
bool LitExp<Derive, val_type>::not_equal(LitExp<Derive, val_type> *b) {
    return !equal(b);
}