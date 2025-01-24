#pragma once
#include "expressionstring.hpp"
#include "litexp.h"
#include <vector>
#include "expressionstring.hpp"
#include "logic_expr.hpp"
#include "arith_expr.hpp"
#include <variant>
#include <memory>
#include <stdexcept>
using namespace std;
//todo fix expressionstring as it shouldnt inherit string
using LogicArithExpression = Expression<bool, long long>;

class Parser{
    public:
        Parser(string &originalExpStr);
        unique_ptr<LogicArithExpression>valExpr;

        string toStr();

    private:
        int currentToken = 0;

        ExpressionString expStr;
        
        unique_ptr<LogicArithExpression>parse_or_exp();

        unique_ptr<LogicArithExpression>parse_and_exp();
        
        //todo check compatibility here, to more quickly know if there
        //is a mismatch between subexpr types
        unique_ptr<LogicArithExpression>parse_eq_exp();

        unique_ptr<LogicArithExpression>parse_rel_exp();

        unique_ptr<LogicArithExpression>parse_add_exp();

        unique_ptr<LogicArithExpression>parse_mul_exp();
       
        unique_ptr<LogicArithExpression>parse_unary_exp();

        unique_ptr<LogicArithExpression>parse_primary_exp();

        unique_ptr<LogicArithExpression>parse_lit();

};


