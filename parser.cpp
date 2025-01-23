using namespace std;
#include "parser.hpp"
#include <stdexcept>

Parser::Parser(string originalExpStr): expStr(originalExpStr){
    parse(originalExpStr);
}

string Parser::toStr(){
    if (valExpr) return valExpr->toStr();
    else return "";
}

void Parser::parse(string str){
    expStr = ExpressionString(str);
    unique_ptr<LogicArithExpression>parse_val(parse_or_exp(str)); 
    valExpr = move(parse_val);
}

unique_ptr<LogicArithExpression>Parser::parse_or_exp(string &str){
    unique_ptr<LogicArithExpression>val = (parse_and_exp(str));

    //if (expStr.startsWith(Operator::OpToString(OperatorType::Or)))
    //decided against using that as I feel it makes the code less readable
    if (expStr.startsWith("||")){
        Operator op = expStr.parseOperator();
        if (op.getType() != OperatorType::Or) 
            throw runtime_error("Operator parsing not working");
        unique_ptr<LogicArithExpression>val2 = (parse_and_exp(str));

        //todo  deal with errors
        //free val
        unique_ptr<LogicArithExpression>nval = make_unique<LogicExp>(get<bool>(val->apply_operator(op, val2.get())));
        return nval;
    }
    else return val;            
}

unique_ptr<LogicArithExpression>Parser::parse_and_exp(string &str){
    unique_ptr<LogicArithExpression>val = (parse_eq_exp(str));

    if (expStr.startsWith("&&")){
        Operator op = expStr.parseOperator();
        unique_ptr<LogicArithExpression>val2 = (parse_eq_exp(str));

        unique_ptr<LogicArithExpression>nval = make_unique<LogicExp>(get<bool>(val->apply_operator(op, val2.get())));
        return nval;
    }
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_eq_exp(string &str){
    unique_ptr<LogicArithExpression>val = (parse_rel_exp(str));
    if (expStr.startsWith("==")){                
        Operator op = expStr.parseOperator();
        unique_ptr<LogicArithExpression>val2 = (parse_rel_exp(str));
        //todo fix this: is this correct? it should get
        //any value, no matter what type it is.
        unique_ptr<LogicArithExpression>nval = make_unique<LogicExp>(get<bool>(val->apply_operator(op, val2.get())));
        return nval;
    }
    else if (expStr.startsWith("!=")){
        Operator op = expStr.parseOperator();
        unique_ptr<LogicArithExpression>val2 = (parse_rel_exp(str));
        unique_ptr<LogicArithExpression>nval = make_unique<LogicExp>(get<bool>(val->apply_operator(op, val2.get())));
        return nval;
    }
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_rel_exp(string &str){
    unique_ptr<LogicArithExpression>val = (parse_add_exp(str));

    vector<string> opStrs = {
        "<",">","<=",">="
    };

    for (auto &opStr: opStrs){
        if (!expStr.startsWith(opStr)) continue;
        Operator op = expStr.parseOperator();
        unique_ptr<LogicArithExpression>val2 = (parse_add_exp(str));
        unique_ptr<LogicArithExpression>nval = make_unique<LogicExp>(get<bool>(val->apply_operator(op, val2.get())));
        return nval;
    }
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_add_exp(string &str){
    unique_ptr<LogicArithExpression>val = (parse_mul_exp(str));
    vector<string> opStrs = {"- ", "+"};
    for (auto &opStr: opStrs){
        if (!expStr.startsWith(opStr)) continue;
        Operator op = expStr.parseOperator();
        unique_ptr<LogicArithExpression>val2 = (parse_mul_exp(str));
        val->apply_operator(op, val2.get());
        return val;  
    }
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_mul_exp(string &str){
    unique_ptr<LogicArithExpression>val = (parse_unary_exp(str));
    vector< string> opStrs = {"*", "/"};
    for (auto &opStr: opStrs){
        if (!expStr.startsWith(opStr)) continue;
        Operator op = expStr.parseOperator();
        unique_ptr<LogicArithExpression>val2 = (parse_unary_exp(str));
        val->apply_operator(op, val2.get()); 
        return val;  
    }
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_unary_exp(string &str){
    if (expStr.startsWith("- ")){
        Operator op = expStr.parseOperator();
        //todo apply the minuss operator with an unary operator function;
        unique_ptr<LogicArithExpression>val = (parse_unary_exp(str));
        val->invert();
        return val;
    }
    unique_ptr<LogicArithExpression>val = parse_primary_exp(str);
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_primary_exp(string &str){
    if (expStr.startsWith("(")){
        string subexpStr = expStr.getSubExpressionString();
        unique_ptr<Parser> subparser = make_unique<Parser>(subexpStr);
        unique_ptr<LogicArithExpression>subexpResult = move(subparser->valExpr);
        return subexpResult;
    }
    unique_ptr<LogicArithExpression>val = parse_lit(str);
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_lit(string &str){
    variant<bool,lli> lit = expStr.parseLit();
    if (bool *b = get_if<bool>(&lit)){
        return make_unique<LogicExp>(*b);
    }
    else if (lli *i = get_if<lli>(&lit)){
        return make_unique<ArithExp>(*i);
    }
    else throw runtime_error("Invalid literal");
}