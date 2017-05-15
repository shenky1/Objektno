
#include "IP_to_FP.h"
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

template <typename T>
string NumberToString(T pNumber)
{
 ostringstream ss;
 ss << pNumber;
 return ss.str();
}

string CharToString(char c){
    ostringstream ss;
    ss << c;
    return ss.str();
}

int IP_to_FP::l_FindOperandIndex(string c, int start){
    int index = start;
    int counter = 0;
    bool passedNum;
    while(true){
        --index;
        if(c[index] == '\(') --counter;
        else if(c[index] == '\)') ++counter;
        else if(isdigit(c[index]) && index == 0) passedNum=true;
        else if(isdigit(c[index]) && !isdigit(c[index-1])) passedNum=true;
        if(passedNum && counter==0) return index;
    }
}

string IP_to_FP::ParseNext(){
    ltrim(mText);

    string c;

    if(mText.empty()) c = "";

    if(!isdigit(mText[0])){
        c = mText.substr(0, 1);
        mText=mText.substr(1, mText.size());
    }

    else if(isdigit(mText[0])){
        int i = 0;
        while(i<=mText.size() && isdigit(mText[i])) ++i;
        c = mText.substr(0, i);
        if(i==mText.size()) mText="";
        else mText=mText.substr(i, mText.size());
    }
    return c;
}


IP_to_FP::Token::Token(std::string str) {
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

IP_to_FP::Token IP_to_FP::getToken() {
    rtrim(mText);
    return Token(ParseNext());
}

string IP_to_FP::Convert(){
    try {
    if(mText.empty()) {
        throw invalid_argument("Wrong input!");
    }
    string output;
    while(!mText.empty()){
        IP_to_FP::Token t = getToken();
        switch(t.type()){
            case operand:
                ValueStack.push(NumberToString(t.value()));
                break;
            case unaryOp:{
                string op1 = ValueStack.top();
                ValueStack.pop();
                string c = "\(";
                c.insert(1, CharToString(t.symbol()));
                c.append(op1);
                c.append("\)");
                ValueStack.push(c);
                break;
            }
            case binaryOp:{
                string op1 = ValueStack.top();
                ValueStack.pop();
                string op2 = ValueStack.top();
                ValueStack.pop();
                string c = "\(";
                c.append(op2);
                c.append(CharToString(t.symbol()));
                c.append(op1);
                c.append("\)");
                ValueStack.push(c);
            }
        }
    }
    if(ValueStack.size()!=1){
        throw std::runtime_error("Final stack size does not equal 1");
    }
    else{
        cout << ValueStack.top();
        return ValueStack.top();
    }
    } catch (...) {
        throw std::invalid_argument("Bad expression!");
    }
}

// trim from start
std::string & IP_to_FP::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &IP_to_FP::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string &IP_to_FP::trim(std::string &s) {
    return ltrim(rtrim(s));
}
