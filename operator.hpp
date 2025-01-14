#pragma once
using namespace std;
#include <string>

enum class OperatorType {
    Add,
    Subtract,
    Multiply,
    Divide,
    And,
    Or,
    Not
};
//todo finish properly inlining methods
class Operator {
    private:
        OperatorType type;
        int size;
        int arity;
    public:
        Operator(string_view op);
        inline OperatorType getType() {return type;};
        //returns the size of the string of the operator
        inline int getSize() const { return size; }
    };
