#include <iostream>
#include "LongAr.h"
#include "Parser.h"

int main() {
    string expr;
    cout << "Enter expression: ";
    getline(cin, expr);
    Parser p(expr.c_str());
    LongAr result = p.Calculate(p.Parse());
    cout << "Result: " << result;
    return 0;
}
