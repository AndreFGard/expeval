#include "litexp.h"
#include <stdexcept>

//todo assert that Derive can be casted to LitExp
//todo finish implementing operators
//todo consider using a static cast to avoid using unimplemented methods
//apparently static cast doesnt do this
//todo use std::concepts instead, because compile time checks rock
template <typename Derive, typename val_type>
void LitExp<Derive, val_type>::apply_operator(Operator op, Expression *b) {
    OperatorType opType = op.getType();
    if (Derive *b2 = is_compatible(dynamic_cast<LitExp<Derive, val_type>>(b))) {
        //Derive thisCopy = *this;
        LitExp<Derive, val_type> thisCast = static_cast<LitExp<Derive, val_type>>(*this);
        
        //todo find some compile time way to enforce all union types being matched
        //Add, Subtract, Multiply, Divide, And, Or, NotEqual, Equal, LessEqual, GreaterEqual, Less, Greater
        switch (opType) {
            case OperatorType::Or:
                thisCast->or_op(b2);
            case OperatorType::And:
                thisCast->and_op(b2);
            case OperatorType::Multiply:
                thisCast->mul(b2);
            case OperatorType::Divide:
                thisCast->div(b2);
            case OperatorType::Equal:
                thisCast->equal(b2);
            case OperatorType::NotEqual:
                !thisCast->equal(b2);
            case OperatorType::GreaterEqual:
                (thisCast->equal(b2) || thisCast->greater(b2));
            case OperatorType::LessEqual:
                !thisCast->greater(b2);
            case OperatorType::Greater:
                thisCast->greater(b2);
            case OperatorType::Less:
                (thisCast->less(b2));
            default:
                throw runtime_error("Unimplemented operator: " + op);
        }

    }
}
