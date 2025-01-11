#include "litexp.h"
#include "logic_expr.hpp"
#include "arith_expr.hpp"
#include <variant>
using namespace std;

class Parser{
    public:
        Parser();
    private:
        variant<ArithExp, LogicExp> parse_val;
        void parse(string expStr){
            
        }

};