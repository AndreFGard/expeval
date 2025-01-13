#include "litexp.h"

//todo finish implementing operators
template <typename Derive, typename val_type>
Derive LitExp<Derive, val_type>::apply_operator(Operator op, LitExp<Derive, val_type> *b) {
    OperatorType opType = op.getType();
    if (Derive *b2 = is_compatible(b)) {
        Derive thisCopy = *this;
        switch (opType) {
        case OperatorType::Or:
            return thisCopy.add(b2);
        }
        default:
            throw std::runtime_error("Unimplemented operator");
    }
}