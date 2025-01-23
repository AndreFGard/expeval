using namespace std;
#include "parser.hpp"
#include <stdexcept>
Parser::Parser(string originalExpStr): valExpr(NULL), expStr(originalExpStr){
    parse(originalExpStr);
}

string Parser::toStr(){
    if (valExpr) return valExpr->toStr();
    else return "";
}

void Parser::parse(string str){
    expStr = ExpressionString(str);
    LogicArithExpression *parse_val(parse_or_exp(str)); 
    valExpr = parse_val;
}

LogicArithExpression *Parser::parse_or_exp(string &str){
    LogicArithExpression *val = (parse_and_exp(str));

    //if (expStr.startsWith(Operator::OpToString(OperatorType::Or)))
    //decided against using that as I feel it makes the code less readable
    if (expStr.startsWith("||")){
        Operator op = expStr.parseOperator();
        if (op.getType() != OperatorType::Or) 
            throw runtime_error("Operator parsing not working");
        LogicArithExpression *val2 = (parse_and_exp(str));

        //todo  deal with errors
        //free val
        LogicArithExpression *nval = new LogicExp(get<bool>(val->apply_operator(op, val2)));
        return nval;
    }
    else return val;            
}

LogicArithExpression *Parser::parse_and_exp(string &str){
    LogicArithExpression *val = (parse_eq_exp(str));

    if (expStr.startsWith("&&")){
        Operator op = expStr.parseOperator();
        LogicArithExpression *val2 = (parse_eq_exp(str));

        LogicArithExpression *nval = new LogicExp(get<bool>(val->apply_operator(op, val2)));
        return nval;
    }
    return val;
}

LogicArithExpression *Parser::parse_eq_exp(string &str){
    LogicArithExpression *val = (parse_rel_exp(str));
    if (expStr.startsWith("==")){                
        Operator op = expStr.parseOperator();
        LogicArithExpression *val2 = (parse_rel_exp(str));
        //todo fix this: is this correct? it should get
        //any value, no matter what type it is.
        LogicArithExpression *nval = new LogicExp(get<bool>(val->apply_operator(op, val2)));
        return nval;
    }
    else if (expStr.startsWith("!=")){
        Operator op = expStr.parseOperator();
        LogicArithExpression *val2 = (parse_rel_exp(str));
        LogicArithExpression *nval = new LogicExp(get<bool>(val->apply_operator(op, val2)));
        return nval;
    }
    return val;
}

LogicArithExpression *Parser::parse_rel_exp(string &str){
    LogicArithExpression *val = (parse_add_exp(str));

    vector<string> opStrs = {
        "<",">","<=",">="
    };

    for (auto &opStr: opStrs){
        if (!expStr.startsWith(opStr)) continue;
        Operator op = expStr.parseOperator();
        LogicArithExpression *val2 = (parse_add_exp(str));
        LogicArithExpression *nval = new LogicExp(get<bool>(val->apply_operator(op, val2)));
        return nval;
    }
    return val;
}

LogicArithExpression *Parser::parse_add_exp(string &str){
    LogicArithExpression *val = (parse_mul_exp(str));
    vector<string> opStrs = {"- ", "+"};
    for (auto &opStr: opStrs){
        if (!expStr.startsWith(opStr)) continue;
        Operator op = expStr.parseOperator();
        LogicArithExpression *val2 = (parse_mul_exp(str));
        val->apply_operator(op, val2);
        return val;  
    }
    return val;
}

LogicArithExpression *Parser::parse_mul_exp(string &str){
    LogicArithExpression *val = (parse_unary_exp(str));
    vector< string> opStrs = {"*", "/"};
    for (auto &opStr: opStrs){
        if (!expStr.startsWith(opStr)) continue;
        Operator op = expStr.parseOperator();
        LogicArithExpression *val2 = (parse_unary_exp(str));
        val->apply_operator(op, val2); 
        return val;  
    }
    return val;
}

LogicArithExpression *Parser::parse_unary_exp(string &str){
    if (expStr.startsWith("- ")){
        Operator op = expStr.parseOperator();
        //todo apply the minuss operator with an unary operator function;
        LogicArithExpression *val = (parse_unary_exp(str));
        val->invert();
        return val;
    }
    LogicArithExpression *val = parse_primary_exp(str);
    return val;
}

LogicArithExpression *Parser::parse_primary_exp(string &str){
    if (expStr.startsWith("(")){
        string subexpStr = expStr.getSubExpressionString();
        Parser *subparser = new Parser(subexpStr);
        LogicArithExpression *subexpResult = subparser->valExpr;
        return subexpResult;
    }
    LogicArithExpression *val = parse_lit(str);
    return val;
}

LogicArithExpression *Parser::parse_lit(string &str){
    variant<bool,lli> lit = expStr.parseLit();
    if (bool *b = get_if<bool>(&lit)){
        return new LogicExp(*b);
    }
    else if (lli *i = get_if<lli>(&lit)){
        return new ArithExp(*i);
    }
    else throw runtime_error("Invalid literal");
}