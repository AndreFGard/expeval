using namespace std;
#include "parser.hpp"
#include <stdexcept>

Parser::Parser(string &originalExpStr): tokenizer(originalExpStr){
    tokenizer = Tokenizer(originalExpStr);
    unique_ptr<LogicArithExpression>parse_val(parse_or_exp()); 
    valExpr = move(parse_val);
}

string Parser::toStr(){
    if (valExpr) return valExpr->toStr();
    else return "";
}


unique_ptr<LogicArithExpression>Parser::parse_or_exp(){
    unique_ptr<LogicArithExpression>val = (parse_and_exp());

    //if (tokenizer.startsWith(Operator::OpToString(OperatorType::Or)))
    //decided against using that as I feel it makes the code less readable
    if (tokenizer.startsWith("||")){
        Operator op = tokenizer.parseOperator();
        if (op.getType() != OperatorType::Or) 
            throw runtime_error("Operator parsing not working");
        unique_ptr<LogicArithExpression>val2 = (parse_and_exp());

        unique_ptr<LogicArithExpression>nval = make_unique<LogicExp>(get<bool>(val->apply_operator(op, val2.get())));
        return nval;
    }
    else return val;            
}

unique_ptr<LogicArithExpression>Parser::parse_and_exp(){
    unique_ptr<LogicArithExpression>val = (parse_eq_exp());

    if (tokenizer.startsWith("&&")){
        Operator op = tokenizer.parseOperator();
        unique_ptr<LogicArithExpression>val2 = (parse_eq_exp());

        unique_ptr<LogicArithExpression>nval = make_unique<LogicExp>(get<bool>(val->apply_operator(op, val2.get())));
        return nval;
    }
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_eq_exp(){
    unique_ptr<LogicArithExpression>val = (parse_rel_exp());
    if (tokenizer.startsWith("==")){                
        Operator op = tokenizer.parseOperator();
        unique_ptr<LogicArithExpression>val2 = (parse_rel_exp());

        unique_ptr<LogicArithExpression>nval = make_unique<LogicExp>(get<bool>(val->apply_operator(op, val2.get())));
        return nval;
    }
    else if (tokenizer.startsWith("!=")){
        Operator op = tokenizer.parseOperator();
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
        if (!tokenizer.startsWith(opStr)) continue;
        Operator op = tokenizer.parseOperator();
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
        if (!tokenizer.startsWith(opStr)) continue;
        Operator op = tokenizer.parseOperator();
        unique_ptr<LogicArithExpression>val2 = (parse_mul_exp());
        return make_unique<ArithExp>(get<lli>(val->apply_operator(op, val2.get()))); 
        //refat return val;  
    }
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_mul_exp(){
    unique_ptr<LogicArithExpression>val = (parse_unary_exp());
    vector< string> opStrs = {"*", "/"};
    for (auto &opStr: opStrs){
        if (!tokenizer.startsWith(opStr)) continue;
        Operator op = tokenizer.parseOperator();
        unique_ptr<LogicArithExpression>val2 = (parse_unary_exp());
        return make_unique<ArithExp>(get<lli>(val->apply_operator(op, val2.get()))); 
        //refat return val;  
    }
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_unary_exp(){
    if (tokenizer.startsWith("- ")){
        Operator op = tokenizer.parseOperator();
        
        unique_ptr<LogicArithExpression>val = (parse_primary_exp());
        //is this error prone?
        //val->invert();
        if (auto castedVal = dynamic_cast<ArithExp *>(val.get())){
            castedVal->invert();
        }
        else throw invalid_argument("- cant be applied to logic expression");
        return val;
    }
    unique_ptr<LogicArithExpression>val = parse_primary_exp();
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_primary_exp(){
    if (tokenizer.startsWith("(")){
        string subexpStr = tokenizer.getSubExpressionString();
        unique_ptr<Parser> subparser = make_unique<Parser>(subexpStr);
        unique_ptr<LogicArithExpression>subexpResult = move(subparser->valExpr);
        return subexpResult;
    }
    unique_ptr<LogicArithExpression>val = parse_lit();
    return val;
}

unique_ptr<LogicArithExpression>Parser::parse_lit(){
    variant<bool,lli> lit = tokenizer.parseLit();
    if (bool *b = get_if<bool>(&lit)){
        return make_unique<LogicExp>(*b);
    }
    else if (lli *i = get_if<lli>(&lit)){
        return make_unique<ArithExp>(*i);
    }
    else throw runtime_error("Invalid literal");
}