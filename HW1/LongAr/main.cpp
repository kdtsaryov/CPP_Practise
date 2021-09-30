#include <iostream>
#include "LongAr.h"

int main() {
    string num1, op, num2;
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter operation(+, -, *, /, %, >, <, >=, <=, ==, !=): ";
    cin >> op;
    cout << "Enter second number: ";
    cin >> num2;

    LongAr n1;
    LongAr n2;
    try {
        n1 = LongAr(num1);
        n2 = LongAr(num2);
    } catch (exception e) {
        cout << "You've entered incorrect number!";
        return 0;
    }

    if (op == "+") {
        LongAr r = n1 + n2;
        cout << "Result: " << r;
    } else if (op == "-") {
        LongAr r = n1 - n2;
        cout << "Result: " << r;
    } else if (op == "*") {
        LongAr r = n1 * n2;
        cout << "Result: " << r;
    } else if (op == "/") {
        LongAr r = n1 / n2;
        cout << "Result: " << r;
    } else if (op == "%") {
        LongAr r = n1 % n2;
        cout << "Result: " << r;
    } else if (op == ">") {
        bool r = n1 > n2;
        cout << "Result: " << (r ? "True" : "False");
    } else if (op == "<") {
        bool r = n1 < n2;
        cout << "Result: " << (r ? "True" : "False");
    } else if (op == ">=") {
        bool r = n1 >= n2;
        cout << "Result: " << (r ? "True" : "False");
    } else if (op == "<=") {
        bool r = n1 <= n2;
        cout << "Result: " << (r ? "True" : "False");
    } else if (op == "==") {
        bool r = n1 == n2;
        cout << "Result: " << (r ? "True" : "False");
    } else if (op == "!=") {
        bool r = n1 != n2;
        cout << "Result: " << (r ? "True" : "False");
    } else {
        cout << "You've entered incorrect operation!";
    }
    return 0;
}
