#pragma once
using namespace std;
#include <string>
#include <unordered_map>

enum class OperatorType {
    Add,
    Subtract,
    Multiply,
    Divide,
    And,
    Or,
    NotEqual,
    Equal,
    LessEqual,
    GreaterEqual,
    Less,
    Greater
};



class Operator: public string{
    private:
        //todo move startswith to a deriver from string
        OperatorType type;
        int size;
        int arity;
    public:
        Operator(string_view op);
        inline OperatorType getType() const;
        //returns the size of the string of the operator
        inline int getSize() const;
};

inline OperatorType Operator::getType() const {
    return type;
};

inline int Operator::getSize() const {
     return size; 
}