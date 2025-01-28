#pragma once
#include "tokenizer.hpp"
#include "litexp.hpp"
#include <vector>
#include "tokenizer.hpp"
#include "logic_expr.hpp"
#include "arith_expr.hpp"
#include <variant>
#include <memory>
#include <stdexcept>
using namespace std;

namespace Expeval {

using LogicArithExpression = Expression<bool, long long>;

class Parser{
    public:
        Parser(string &originalExpStr);
        

        string toStr();
        inline unique_ptr<LogicArithExpression>& getValExpr();
        inline void setValExpr(unique_ptr<LogicArithExpression>& ptr);
    private:
        int currentToken = 0;

        Tokenizer tokenizer;
        
        unique_ptr<LogicArithExpression>valExpr;
        unique_ptr<LogicArithExpression>parse_or_exp();

        unique_ptr<LogicArithExpression>parse_and_exp();
        
        unique_ptr<LogicArithExpression>parse_eq_exp();

        unique_ptr<LogicArithExpression>parse_rel_exp();

        unique_ptr<LogicArithExpression>parse_add_exp();

        unique_ptr<LogicArithExpression>parse_mul_exp();
       
        unique_ptr<LogicArithExpression>parse_unary_exp();

        unique_ptr<LogicArithExpression>parse_primary_exp();

        unique_ptr<LogicArithExpression>parse_lit();

};

inline unique_ptr<LogicArithExpression>& Parser::getValExpr(){
    return valExpr;
}
inline void Parser::setValExpr(unique_ptr<LogicArithExpression>& ptr){
    valExpr = move(ptr);
}

}