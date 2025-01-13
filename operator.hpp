#pragma once
using namespace std;

enum class OperatorType {
    Add,
    Subtract,
    Multiply,
    Divide,
    And,
    Or,
    Not
};
class Operator {
    private:
        OperatorType type;
        int size;
    public:
        Operator(string_view op);
        inline OperatorType getType();
        //returns the size of the string of the operator
        inline int getSize();
};
