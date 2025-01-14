#include "litexp.h"
#include <stdexcept>

//todo assert that Derive can be casted to LitExp
//todo finish implementing operators
//todo consider using a static cast to avoid using unimplemented methods
//apparently static cast doesnt do this
//todo use std::concepts instead, because compile time checks rock
template <typename Derive, typename val_type>
Derive LitExp<Derive, val_type>::apply_operator(Operator op, LitExp<Derive, val_type> *b) {
    OperatorType opType = op.getType();
    if (Derive *b2 = is_compatible(b)) {
        //Derive thisCopy = *this;
        LitExp<Derive, val_type> thisCast = static_cast<LitExp<Derive, val_type>>(*this);
        
        //todo find some compile time way to enforce all union types being matched
        //Add, Subtract, Multiply, Divide, And, Or, NotEqual, Equal, LessEqual, GreaterEqual, Less, Greater
        switch (opType) {
            case OperatorType::Or:
                return thisCast->or_op(b2);
            case OperatorType::And:
                return thisCast->and_op(b2);
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
            default:
                throw runtime_error("Unimplemented operator: " + op);
        }

    }
}
