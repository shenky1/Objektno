#include "Expression.h"
#include <sstream>
#include <iterator>
#include <iostream>
#include <string>
#include <math.h>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace std;

Expression::Token::Token(std::string str) {
    if(str.compare("+") == 0 || str.compare("-") == 0 || str.compare("*") == 0 || str.compare("/") == 0 || str.compare("^") == 0) {
        mtype = binaryOp;
        msymbol = str[0];
    } else if (str.compare("~") == 0) {
        mtype = unaryOp;
        msymbol = str[0];
    } else {
        istringstream convert(str);
        if (!(convert >> mval))
            mval = 0;
        mtype = operand;
    }
}

Expression::Token Expression::getToken() {
    mText = Expression::trim(mText);
    int spaceIndex = getText().find(' ');

    if(spaceIndex != -1) {
        std::string nextToken = getText().substr(0, spaceIndex);
        mText = mText.substr(spaceIndex + 1, mText.size());
        Expression::Token token(nextToken);
        return token;
    } else {
        Expression::Token token(mText);
        mText = "";
        return token;
    }
}

Expression::Value Expression::evaluate(){
    try {
    if(mText.empty()) {
        throw invalid_argument("Wrong input!");
    }
    Expression::Token t = getToken();
   if(t.type() == unaryOp){
        return -evaluate();
   }
   else if(t.type() == binaryOp){
        int prvi = evaluate();
        int drugi = evaluate();
        switch (t.symbol()){
        case '+':
            return prvi+drugi;
            break;
        case '-':
            return prvi-drugi;
            break;
        case '*':
            return prvi*drugi;
            break;
        case '/':
            return prvi/drugi;
            break;
        default:
            return pow(prvi, drugi);
            break;
        }
   } else {
      return t.value();
   }
    } catch (...) {
        throw std::invalid_argument("Bad expression!");
    }
}

// trim from start
std::string & Expression::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &Expression::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string &Expression::trim(std::string &s) {
    return ltrim(rtrim(s));
}
