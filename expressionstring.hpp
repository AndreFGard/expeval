#pragma once
#include <string>
using namespace std;
#include <string_view>
#include "operator.hpp"
#include <variant>
typedef long long int lli;
class ExpressionString{
    public:
        ExpressionString(string_view str);
        string getOriginalString();
        
        inline bool startsWith(string prefix);
        Operator parseOperator();

        string getSubExpressionString();

        inline string_view getView();

        variant<bool, lli> parseLit();

    private:
        inline void moveView(int n);

        inline void stripView();

        string_view view;
        int index =0;
        string original;
};


inline bool ExpressionString::startsWith(string prefix){
    return (view.rfind(prefix,0) == 0);
}

inline string_view ExpressionString::getView(){
    return view;
}

inline void ExpressionString::moveView(int n){
    view = view.substr(n);
    index+=n;
    stripView();
}

inline void ExpressionString::stripView(){
    while (view[0] == ' '){
        view = view.substr(1);
        index++;
    }
    while (*(view.rbegin()) == ' '){
        view = view.substr(0, view.size()-1);
    }

}