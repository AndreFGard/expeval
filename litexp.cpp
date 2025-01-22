#include "litexp.h"
#include <stdexcept>

//todo assert that Derive can be casted to LitExp
//todo finish implementing operators
//todo consider using a static cast to avoid using unimplemented methods
//apparently static cast doesnt do this
//todo use std::concepts instead, because compile time checks rock

template <typename Derive, typename val_type>
void LitExp<Derive, val_type>::apply_operator(Operator op, LogicArithExpression *b) {
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
            thisCast->or_op(b2); return;
        case OperatorType::And:
            thisCast->and_op(b2); return;
        case OperatorType::Add:
            thisCast->add(b2);return;
        case OperatorType::Multiply:
            thisCast->mul(b2); return;
        case OperatorType::Divide:
            thisCast->div(b2); return;
        case OperatorType::Equal:
            thisCast->equal(b2); return;
        case OperatorType::NotEqual:
            !thisCast->equal(b2); return;
        case OperatorType::GreaterEqual:
            (thisCast->equal(b2) || thisCast->greater(b2));
        case OperatorType::LessEqual:
            !thisCast->greater(b2); return;
        case OperatorType::Greater:
            thisCast->greater(b2); return;
        case OperatorType::Less:
            (thisCast->less(b2)); return;
        case OperatorType::Subtract:
            (thisCast->sub(b2)); return;
        default:
            throw runtime_error("Unimplemented operator: " + op);
    }
}