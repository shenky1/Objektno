
#ifndef ARITMETICKIIZRAZI4_H_INCLUDED
#define ARITMETICKIIZRAZI4_H_INCLUDED

#include <string>
#include <vector>
#include <istream>
#include<stack>

class IP_to_FP{
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

    IP_to_FP() : mText("") {}
    IP_to_FP(std::string text) : mText(text) {};

    std::string Convert();
    std::string getText() {return mText;}

    std::string ParseNext();

    // trim from start
    static inline std::string &ltrim(std::string &s);
    // trim from end
    static inline std::string &rtrim(std::string &s);
    // trim from both ends
    static inline std::string &trim(std::string &s);

private:
    int l_FindOperandIndex(std::string c, int start);
    int r_FindOperandIdnex(std::string c, int start);
    std::string mText;
    Token getToken();
    std::stack<std::string> ValueStack;
};
#endif
