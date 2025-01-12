#include "logic_expr.hpp"
#include <stdexcept>
#include <string>
using namespace std;

//may throw
LogicExp::LogicExp(string expStr): expStr(expStr){
    if (expStr == "true") val = true;
    else if (expStr == "false") val = false;
    else throw invalid_argument("Invalid argument: not a boolean value");
}

inline bool LogicExp::getVal() const{
    return val;
}

//todo make dynamic cast
LogicExp *LogicExp::is_compatible(LitExp *b){
    return dynamic_cast<LogicExp *>(b);
}

const bool &LogicExp::add (LitExp *b) {
    if (const LogicExp *castedb = is_compatible(b)){
        val = (val || castedb->getVal());
        return val;
    }
    else throw invalid_argument("Invalid argument: different types");
}


int main(){
 LogicExp a("tru");
 LogicExp b("false");
}