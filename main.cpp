#include <iostream>
#include <string>

#include "Expression.h"
#include "IPExpression.h"
#include "Transform.h"

using namespace std;


void checkPre(std::string const & izraz, int vrijednost){
   Expression expr(izraz);
   if(expr.evaluate() == vrijednost ) cout << "OK\n";
   else                               cout << "ERROR\n";
}

void checkPost(std::string const & izraz, int vrijednost){
   IPExpression expr(izraz);
   if(expr.evaluate() == vrijednost ) cout << "OK\n";
   else                               cout << "ERROR\n";
}

void checkTr(std::string const & izraz, int vrijednost){
   Transform expr(izraz);
   if(expr.evaluate() == vrijednost ) cout << "OK\n";
   else                               cout << "ERROR\n";
}

int main(int argc, char *argv[])
{
    cout << "Prefix form evaluation ===============\n";
    checkPre("+ 2 3", 5);
    checkPre("+~3*^3-3 1 2", 15);
    checkPre("~ * ^ 2 3 3 ", -24);

    cout << "Postfix form evaluation ===============\n";

    checkPost("3 2 4 * 1 - +", 10);
    checkPost("3 2 ^ 4 7 * - 9 3 1 - * +", -1);
    checkPost("2 3 4 5 - * + 2 3 ^ -", -9);
    checkPost(" 3 12 11 - ^ ~ 4 1 + 7 * - 9 3 2 1 - ^ * +  ", -11);

    cout << "Infix form evaluation ===============\n";
    checkTr("2 + 3*( 4- 5) - 2^3", -9);
    checkTr("3^2-4*7+9*(3-1)", -1);
    checkTr("~3^(12-11)-(4+1)*7+9*(3^(2-1))", -11);

    return 0;
}
