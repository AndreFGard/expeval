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
        
        variant<bool,long long> apply_operator(Operator op, Expression *b) override;

        virtual bool less_equal(LitExp *b);
        virtual bool greater_equal(LitExp *b);
        virtual bool not_equal(LitExp *b);


        
        //apply binary operator

        // const inline string getExpStr() const { return expStr; }
        // friend ostream &operator<<(ostream &os, const Expr &expr);
    protected:
        virtual Derive* is_compatible(Expression *b) = 0;
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

template <typename Derive, typename val_type>
variant<bool,long long> LitExp<Derive, val_type>::apply_operator(Operator op, Expression *b) {
    OperatorType opType = op.getType();

    //Hereby, I declare: this static cast shall work
    //or not, then either the unimplemented operator or the implemented operator upon it's time to check
    //shal throw
    auto *b2 = static_cast<Derive *>(b);
    //Derive thisCopy = *this;
    LitExp<Derive, val_type> *thisCast = static_cast<LitExp<Derive, val_type>*>(this);

    //todo find some compile time way to enforce all union types being matched
    //Add, Subtract, Multiply, Divide, And, Or, NotEqual, Equal, LessEqual, GreaterEqual, Less, Greater
    switch (opType) {
        case OperatorType::Or:
            return thisCast->or_op(b2);
        case OperatorType::And:
            return thisCast->and_op(b2);
        case OperatorType::Add:
            return thisCast->add(b2);
        case OperatorType::Multiply:
            return thisCast->mul(b2);
        case OperatorType::Divide:
            return thisCast->div(b2);
        case OperatorType::Equal:
            return thisCast->equal(b2);
        case OperatorType::NotEqual:
            return !thisCast->equal(b2);
        case OperatorType::GreaterEqual:
            return (thisCast->equal(b2) || thisCast->greater(b2));
        case OperatorType::LessEqual:
            return !thisCast->greater(b2);
        case OperatorType::Greater:
            return thisCast->greater(b2);
        case OperatorType::Less:
            return (thisCast->less(b2));
        case OperatorType::Subtract:
            return (thisCast->sub(b2));
        default:
            throw runtime_error("Unimplemented operator: " + op);
    }
}

