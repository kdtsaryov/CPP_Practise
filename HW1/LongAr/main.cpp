#include <iostream>
#include <vector>

using namespace std;

class LongAr {
public:
    LongAr() = default;

    static const int BASE = 10;
    vector<int> digits;
    bool isNeg{};

    void RemoveZeroes() {
        while (this->digits.size() > 1 && this->digits.back() == 0) {
            this->digits.pop_back();
        }
        if (this->digits.size() == 1 && this->digits[0] == 0) {
            this->isNeg = false;
        }
    }

    explicit LongAr(string str) {
        if (str[0] == '-') {
            str = str.substr(1);
            this->isNeg = true;
        } else {
            this->isNeg = false;
        }
        for (long long i = str.length(); i > 0; i--) {
            this->digits.push_back(stoi(str.substr(i - 1, 1)));
        }
        this->RemoveZeroes();
    }

    string CreateString() {
        if (this->digits.empty()) {
            return "0";
        } else {
            string str;
            if (this->isNeg) {
                str += '-';
            }
            str += to_string(this->digits.back());
            for (long long i = this->digits.size() - 2; i >= 0; --i) {
                str += to_string(this->digits[i]);
            }
            return str;
        }
    }

    LongAr operator-() const {
        LongAr copy(*this);
        copy.isNeg = !copy.isNeg;
        return copy;
    }
};

bool operator==(const LongAr &left, const LongAr &right) {
    if (left.isNeg != right.isNeg) return false;
    if (left.digits.size() == 1 && left.digits[0] == 0) {
        if (right.digits.size() == 1 && right.digits[0] == 0) {
            return true;
        } else {
            return false;
        }
    }
    if (left.digits.size() != right.digits.size()) {
        return false;
    }
    for (long long i = 0; i < left.digits.size(); ++i) {
        if (left.digits[i] != right.digits[i]) {
            return false;
        }
    }
    return true;
}

bool operator<(const LongAr &left, const LongAr &right) {
    if (left == right) {
        return false;
    }
    if (left.isNeg) {
        if (right.isNeg) {
            return ((-right) < (-left));
        } else {
            return true;
        }
    } else if (right.isNeg) {
        return false;
    } else {
        if (left.digits.size() != right.digits.size()) {
            return left.digits.size() < right.digits.size();
        } else {
            for (long long i = left.digits.size() - 1; i >= 0; --i) {
                if (left.digits[i] != right.digits[i]) {
                    return left.digits[i] < right.digits[i];
                }
            }
            return false;
        }
    }
}

bool operator<=(const LongAr &left, const LongAr &right) {
    return (left < right || left == right);
}

bool operator>=(const LongAr &left, const LongAr &right) {
    return !(left < right);
}

bool operator>(const LongAr &left, const LongAr &right) {
    return !(left <= right);
}

LongAr operator-(LongAr left, const LongAr &right);

LongAr operator+(LongAr left, const LongAr &right) {
    if (left.isNeg) {
        if (right.isNeg) {
            return -(-left + (-right));
        } else {
            return right - (-left);
        }
    } else if (right.isNeg) {
        return left - (-right);
    }
    int c = 0;
    for (long long i = 0; i < max(left.digits.size(), right.digits.size()) || c != 0; ++i) {
        if (i == left.digits.size()) {
            left.digits.push_back(0);
        }
        left.digits[i] += c + (i < right.digits.size() ? right.digits[i] : 0);
        c = left.digits[i] >= LongAr::BASE;
        if (c != 0) {
            left.digits[i] -= LongAr::BASE;
        }
    }
    return left;
}

LongAr operator-(LongAr left, const LongAr &right) {
    if (right.isNeg) {
        return left + (-right);
    } else if (left.isNeg) {
        return -(-left + right);
    } else if (left < right) {
        return -(right - left);
    }
    int c = 0;
    for (long long i = 0; i < right.digits.size() || c != 0; ++i) {
        left.digits[i] -= c + (i < right.digits.size() ? right.digits[i] : 0);
        c = left.digits[i] < 0;
        if (c != 0) left.digits[i] += LongAr::BASE;
    }
    left.RemoveZeroes();
    return left;
}

int main() {
    string num1, op, num2;
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter operation(+, -, >, <, >=, <=, ==): ";
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
        cout << "Result: " << r.CreateString();
    } else if (op == "-") {
        LongAr r = n1 - n2;
        cout << "Result: " << r.CreateString();
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
    } else {
        cout << "You've entered incorrect operation!";
    }

    return 0;
}
