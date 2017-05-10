#include <iostream>
#include "Expression.h"
#include "IPExpression.h"
#include "Transform.h"

using namespace std;

int main()
{
    std::string expr = "~ * ^ 2 3 3 ";
    Expression expr3(expr);
    cout << expr  << " = "  << expr3.evaluate()  << endl;

    expr = " 3 2 4 * 1 - +";
    IPExpression ipexp1(expr);
    cout  << expr  << " = "  << ipexp1.evaluate()  << endl;

    expr = "2 + 3";
    Transform t = Transform(expr);
    t.print_postfix(cout);
    return 0;
}
