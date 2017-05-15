#ifndef ARITMETICKIIZRAZI_H_INCLUDED
#define ARITMETICKIIZRAZI_H_INCLUDED

#include <string>
#include <vector>
#include <istream>
/**  Klasa za izračunavanje aritmetičkog izraza u poljskoj notaciji.
 *  Binarne operacije su +,-,*,/
 *  Unarne operacije ~ (negacija). Koristimo ~ umjesto - kako bismo
 *  mogli razlikovati unarnu od binarne operacije prema simbolu.
 */
class Expression{
public:
    /** tip izraza */
    using Value = int;

    /** tip tokena */
    enum TokenType {
        operand,
        unaryOp,
        binaryOp
    };

    /**
    * Pomoćna klasa koja predstavlja element izraza. Ako je izraz operand
    * imat će vrijednost. Ako se radi o operaciji vrijednost može biti proizvoljna.
    */
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

    /** Konstrukcija praznog izraza */
    Expression() : mText("") {}

    /** Konstrukcija izraza iz stringa.
	* text mora sadržavati aritmetički izraz u poljskoj notaciji. Sprema
	* se u varijablu članicu mText.
	*/
    Expression(std::string text) : mText(text) {};

    /** Izračunaj vrijednost izraza. To je rekurzivna metoda koja prilikom izračunavanja
    * može uništiti izraz.
    */
    Value evaluate();
    std::string getText() {return mText;}

    std::string ParseNext();

    // trim from start
    static inline std::string &ltrim(std::string &s);
    // trim from end
    static inline std::string &rtrim(std::string &s);
    // trim from both ends
    static inline std::string &trim(std::string &s);

   private:
    std::string mText;
   /** Daje sljedeći token sadržan u izrazu. */
    Token getToken();

};

#endif
