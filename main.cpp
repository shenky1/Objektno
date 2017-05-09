#include <iostream>
#include "Expression.h"

using namespace std;

int main()
{
    std::string expr = "/ + 5 0 0";
    Expression expr3(expr);
    cout << expr  << " = "  << expr3.evaluate()  << endl;
    return 0;
}
