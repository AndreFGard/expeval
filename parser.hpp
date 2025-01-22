#pragma once
#include "expressionstring.hpp"
#include "litexp.h"
#include <vector>
#include "expressionstring.hpp"
#include "logic_expr.hpp"
#include "arith_expr.hpp"
#include <variant>
#include <stdexcept>
using namespace std;
//todo fix expressionstring as it shouldnt inherit string
using LogicArithExpression = Expression<bool, long long>;

class Parser{
    public:
        Parser(string originalExpStr);
        LogicArithExpression *valExpr;

        string toStr();

    private:
        int currentToken = 0;

        ExpressionString expStr;
        
        void parse(string str);

        LogicArithExpression *parse_or_exp(string &str);

        LogicArithExpression *parse_and_exp(string &str);
        
        //todo check compatibility here, to more quickly know if there
        //is a mismatch between subexpr types
        LogicArithExpression *parse_eq_exp(string &str);

        LogicArithExpression *parse_rel_exp(string &str);

        LogicArithExpression *parse_add_exp(string &str);

        LogicArithExpression *parse_mul_exp(string &str);
       
        LogicArithExpression *parse_unary_exp(string &str);

        LogicArithExpression *parse_primary_exp(string &str);

        LogicArithExpression *parse_lit(string &str);

};


