#include "Transform.h"
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
#include "IPExpression.h"

using namespace std;

Transform::Transform(string text){
    init(text);
}

void Transform::init(string text){
    mText = text;
    mDelayOps = stack<Token>();
    mOperands = stack<Value>();
    mOutput = Convert();
}

Transform::Token::Token(std::string str) {
    switch(str[0]){
        case '~':
            symbol = str[0];
            priority = 3;
            type = unaryOp;
            break;
        case '(':
            symbol = str[0];
            type = leftParen;
            priority = 4;
            break;
        case ')':
            symbol = str[0];
            type = rightParen;
            priority = 4;
            break;
        case '=':
            symbol = str[0];
            type = endToken;
            break;
        case '^':
            symbol=str[0];
            priority=3;
            type = binaryOp;
            break;
        case '*':
            symbol = str[0];
            priority = 2;
            type = binaryOp;
            break;
        case '/':
            symbol = str[0];
            priority = 2;
            type = binaryOp;
            break;
        case '+':
            symbol = str[0];
            priority = 1;
            type = binaryOp;
            break;
        case '-':
            symbol = str[0];
            priority = 1;
            type = binaryOp;
            break;
        default:{
            istringstream convert(str);
            if (!(convert >> val))
                val = 0;
            type = operand;
        }
    }
}

Transform::Token Transform::getToken() {
    mText = Transform::trim(mText);
    int spaceIndex = getText().find(' ');

    if(spaceIndex != -1) {
        std::string nextToken = getText().substr(0, spaceIndex);
        mText = mText.substr(spaceIndex + 1, mText.size());
        //std::cout << mText << std::endl;
        Transform::Token token(nextToken);
        return token;
    } else {
        Transform::Token token(mText);
        mText = "";
        return token;
    }
}

list<Transform::Token> Transform::Convert(){
    list<Token> output;
    while (!mText.empty()){
        Token t = getToken();
        if (t.getType()==operand){
            output.push_back(t);
        }
        else if(t.getType()==rightParen){
            while(!mDelayOps.empty() && mDelayOps.top().getType()!=leftParen){
                output.push_back(mDelayOps.top());
                mDelayOps.pop();
            }
            mDelayOps.pop();
        }
        else if(t.getType()==leftParen){
            mDelayOps.push(t);
        }
        else if(t.getPriority()<3){
            while(mDelayOps.size()!=0){
                if(mDelayOps.top().getPriority()>=t.getPriority() && mDelayOps.top().getType()!=leftParen){
                output.push_back(mDelayOps.top());
                mDelayOps.pop();
                }
                else break;
            }
            mDelayOps.push(t);
        }
        else if(t.getPriority()==3){
            mDelayOps.push(t);
        }
    }
    while(!mDelayOps.empty()){
        output.push_back(mDelayOps.top());
        mDelayOps.pop();
    }
    return output;
}

string Transform::getOutput(){
    string output;
    std::ostringstream ss;
    for(list<Token>::iterator it = mOutput.begin(); it != mOutput.end(); ++it){
        if(it->getType()==operand) { ss << it->getValue() <<" ";
        } else { ss << it->getSymbol() << " ";
      }
    }
    output.append(ss.str());
    return output;
}

void Transform::print_postfix(std::ostream & o){
    o << endl << "printing POSTORDER: ";
    for(list<Token>::iterator it = mOutput.begin(); it!=mOutput.end(); ++it){
        if(it->getType()==operand) o << it->getValue();
        else o << it->getSymbol();
    }
    o << endl;
}

void Transform::printTokens(list<Token> li){
    cout << endl << "Output current state: ";
    for(list<Token>::iterator it = li.begin(); it!=li.end(); ++it){
        if(it->getType()==operand) cout << it->getValue();
        else cout << it->getSymbol();
    }
}

int Transform::evaluate() {
    IPExpression expr(getOutput());
    return expr.evaluate();
}

// trim from start
std::string & Transform::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &Transform::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string &Transform::trim(std::string &s) {
    return ltrim(rtrim(s));
}
