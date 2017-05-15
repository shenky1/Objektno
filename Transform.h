#ifndef ARITMETICKIIZRAZI3_H_INCLUDED
#define ARITMETICKIIZRAZI3_H_INCLUDED

#include <string>
#include<stack>
#include<list>

/**  Klasa se incijalizira izrazom u infix formi koji automatski konvertira u
 *   postfix formu i nudi metodu evaluate() te print_postfix().
 */
class Transform{
public:
    // tip izraza
    using Value = int;
    // endToken je uveden da označi završetak ulaznog niza tokena
    // leftParen je otvorena zagrada, a  rightParen je zatvorena zagrada
    enum TokenType {operand, unaryOp, binaryOp, leftParen, rightParen, endToken};

    // pomoćna klasa koja predstavlja element izraza
    struct Token{
        public:
            TokenType getType() const { return type; }
            char getSymbol() const { return symbol; }
            Value getValue() const { return val; }
            int getPriority() const {return priority; }
            Token(std::string str);

        private:
            char symbol;
            Value val;
            TokenType type;
            int priority;
    };

    // Konstrukcija praznog izraza
    Transform() {}
    // Konstrukcija izraza iz stringa.
    // text mora sadržavati aritmetički izraz u infix notaciji
    Transform(std::string text);

    // Inicijalizacija iz stringa.
    // text mora sadržavati aritmetički izraz u infix notaciji
    void init(std::string text);

    //Konverzija u Preorder (IP) notaciju:
    std::list<Token> Convert();
    // Izračunaj vrijednost izraza.
    Value evaluate();
    // Ispiši postfix verziju izraza
    void print_postfix(std::ostream & o);

    // trim from start
    static inline std::string &ltrim(std::string &s);
    // trim from end
    static inline std::string &rtrim(std::string &s);
    // trim from both ends
    static inline std::string &trim(std::string &s);

    std::string getText(){return mText;}

    std::string getOutput();


private:
    // Ulazni string sa infix izrazom
    std::string mText;
    std::string::iterator mNextToken;
    // Stog odgođenih operacija
    std::stack<Token> mDelayOps;
    // Lista tokena u postfix formi (inverzna poljska notacija)
    std::list<Token> mOutput;
    // Stack za izračunavanje izraza
    std::stack<Value> mOperands;

    // Rutina koja čini transformaciju iz infix u prefix formu
    void transform();
    // Daje sljedeći token sadržan u ulaznom nizu
    Token getToken();

    void printTokens(std::list<Token> li);
};
#endif
