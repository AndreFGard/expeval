#include "logic_expr.hpp"
#include <stdexcept>
using namespace std;

LogicExp::LogicExp(string &expStr){
    val =( expStr.find("true") != string::npos);
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

}