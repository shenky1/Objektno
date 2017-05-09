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
        std::cout << mText << std::endl;
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
        std::cout << prvi << std::endl;
        int drugi = evaluate();
        std::cout << drugi << std::endl;
        if(t.symbol() == '+') return prvi + drugi;
        else if(t.symbol() == '-') return prvi - drugi;
        else if(t.symbol() == '*') return prvi * drugi;
        else if(t.symbol() == '/') if(drugi == 0) throw invalid_argument("Division by zero!"); else return prvi / drugi;
        else return pow(prvi, drugi);
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
