#ifndef ARITMETICKIIZRAZI2_H_INCLUDED
#define ARITMETICKIIZRAZI2_H_INCLUDED

#include <string>
#include <vector>
#include <istream>
#include<stack>

class IPExpression{
public:
    using Value = int;
    enum TokenType{
        unaryOp,
        binaryOp,
        operand
    };

    struct Token{
    public:
        TokenType type() const { return mtype; }
        char symbol() const { return msymbol; }
        Value value() const { return mval; }
        Token(std::string str);

    private:
        char msymbol;
        Value mval;
        TokenType mtype;
    };

    IPExpression() : mText("") {}
    IPExpression(std::string text) : mText(text) {};

    Value evaluate();
    std::string getText() {return mText;}

    // trim from start
    static inline std::string &ltrim(std::string &s);
    // trim from end
    static inline std::string &rtrim(std::string &s);
    // trim from both ends
    static inline std::string &trim(std::string &s);

private:
    std::string mText;
    Token getToken();
    std::stack<Value> ValueStack;
};
#endif
