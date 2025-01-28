#include "tokenizer.hpp"
using namespace std;
using namespace Expeval;

Operator Tokenizer::parseOperator(){
    auto temp = Operator(view.substr(0, 2));
    moveView(temp.getSize());
    stripView();
    return temp;
}

string Tokenizer::getSubExpressionString(){
    int firstOpening = 0, lastClosing =-1;
    int levelsToIgnore = 0;
    
    for (int i=1;i<view.length();i++){
        if (view[i] == '('){
            levelsToIgnore++;
        }
        if (view[i] == ')'){
            if (levelsToIgnore == 0){
                lastClosing = i;
                break;
            }
            else levelsToIgnore--;
        }
    }
    string temp = string(view).substr(1+1, lastClosing-firstOpening-1-1-1); //+1 because of spaces
    moveView(lastClosing+1);
    return temp;
}

Tokenizer::Tokenizer(string_view str){
    view = string_view(str);
    stripView();
    original = string(str);
}

string Tokenizer::getOriginalString(){
    return original;
}


variant<bool, lli> Tokenizer::parseLit(){
    if (startsWith("true")){
        moveView(4);
        return true;
    }
    else if (startsWith("false")){
        moveView(5);
        return false;
    }
    else {
        string numS;
        int stIdx = 0;
        int negative = 1;
        if(view[0] == '-'){
            negative = -1;
            moveView(1);
        }

        while (isdigit(view[stIdx])){
            numS += view[stIdx];
            //moveView(1);
            //todo perhaps i could deal with subtraction right here
            stIdx++;
        }
        moveView(stIdx);
        return negative *stoll(numS);

    }
}

