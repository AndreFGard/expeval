using namespace std;
#include "parser.hpp"
#include <stdexcept>

Parser::Parser(string &originalExpStr): expStr(originalExpStr){
    expStr = ExpressionString(originalExpStr);
    unique_ptr<LogicArithExpression>parse_val(parse_or_exp()); 
    valExpr = move(parse_val);
}

string Parser::toStr(){
    if (valExpr) return valExpr->toStr();
    else return "";
}


unique_ptr<LogicArithExpression>Parser::parse_or_exp(){
    unique_ptr<LogicArithExpression>val = (parse_and_exp());

    //if (expStr.startsWith(Operator::OpToString(OperatorType::Or)))
    //decided against using that as I feel it makes the code less readable
    if (expStr.startsWith("||")){
        Operator op = expStr.parseOperator();
        if (op.getType() != OperatorType::Or) 
            throw runtime_error("Operator parsing not working");
        unique_ptr<LogicArithExpression>val2 = (parse_and_exp());

        //todo  deal with errors
        //free val
        unique_ptr<LogicArithExpression>nval = make_unique<LogicExp>(get<bool>(val->apply_operator(op, val2.get())));
        return nval;
    }
    else return val;            
}

unique_ptr<LogicArithExpression>Parser::parse_and_exp(){
    unique_ptr<LogicArithExpression>val = (parse_eq_exp());

    if (expStr.startsWith("&&")){
        Operator op = expStr.parseOperator();
        unique_ptr<LogicArithExpression>val2 = (parse_eq_exp());

        unique_ptr<LogicArithExpression>nval = make_unique<LogicExp>(get<bool>(val->apply_operator(op, val2.get())));
        return nval;
    }
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_eq_exp(){
    unique_ptr<LogicArithExpression>val = (parse_rel_exp());
    if (expStr.startsWith("==")){                
        Operator op = expStr.parseOperator();
        unique_ptr<LogicArithExpression>val2 = (parse_rel_exp());
        //todo fix this: is this correct? it should get
        //any value, no matter what type it is.
        unique_ptr<LogicArithExpression>nval = make_unique<LogicExp>(get<bool>(val->apply_operator(op, val2.get())));
        return nval;
    }
    else if (expStr.startsWith("!=")){
        Operator op = expStr.parseOperator();
        unique_ptr<LogicArithExpression>val2 = (parse_rel_exp());
        unique_ptr<LogicArithExpression>nval = make_unique<LogicExp>(get<bool>(val->apply_operator(op, val2.get())));
        return nval;
    }
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_rel_exp(){
    unique_ptr<LogicArithExpression>val = (parse_add_exp());

    vector<string> opStrs = {
        "<",">","<=",">="
    };

    for (auto &opStr: opStrs){
        if (!expStr.startsWith(opStr)) continue;
        Operator op = expStr.parseOperator();
        unique_ptr<LogicArithExpression>val2 = (parse_add_exp());
        unique_ptr<LogicArithExpression>nval = make_unique<LogicExp>(get<bool>(val->apply_operator(op, val2.get())));
        return nval;
    }
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_add_exp(){
    unique_ptr<LogicArithExpression>val = (parse_mul_exp());
    vector<string> opStrs = {"- ", "+"};
    for (auto &opStr: opStrs){
        if (!expStr.startsWith(opStr)) continue;
        Operator op = expStr.parseOperator();
        unique_ptr<LogicArithExpression>val2 = (parse_mul_exp());
        val->apply_operator(op, val2.get());
        return val;  
    }
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_mul_exp(){
    unique_ptr<LogicArithExpression>val = (parse_unary_exp());
    vector< string> opStrs = {"*", "/"};
    for (auto &opStr: opStrs){
        if (!expStr.startsWith(opStr)) continue;
        Operator op = expStr.parseOperator();
        unique_ptr<LogicArithExpression>val2 = (parse_unary_exp());
        val->apply_operator(op, val2.get()); 
        return val;  
    }
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_unary_exp(){
    if (expStr.startsWith("- ")){
        Operator op = expStr.parseOperator();
        //todo apply the minuss operator with an unary operator function;
        unique_ptr<LogicArithExpression>val = (parse_unary_exp());
        val->invert();
        return val;
    }
    unique_ptr<LogicArithExpression>val = parse_primary_exp();
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_primary_exp(){
    if (expStr.startsWith("(")){
        string subexpStr = expStr.getSubExpressionString();
        unique_ptr<Parser> subparser = make_unique<Parser>(subexpStr);
        unique_ptr<LogicArithExpression>subexpResult = move(subparser->valExpr);
        return subexpResult;
    }
    unique_ptr<LogicArithExpression>val = parse_lit();
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_lit(){
    variant<bool,lli> lit = expStr.parseLit();
    if (bool *b = get_if<bool>(&lit)){
        return make_unique<LogicExp>(*b);
    }
    else if (lli *i = get_if<lli>(&lit)){
        return make_unique<ArithExp>(*i);
    }
    else throw runtime_error("Invalid literal");
}