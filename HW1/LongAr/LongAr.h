#include <vector>

using namespace std;

/// Класс, реализующий длинную арифметику
class LongAr {
public:
    LongAr() = default;

    // Основание системы счисления
    static const int BASE = 10;
    // Цифры
    vector<short int> digits;
    // Знак числа
    bool isNeg{};

    /// Метод, удаляющий ведущие нули
    void RemoveZeroes() {
        while (this->digits.size() > 1 && this->digits.back() == 0) {
            this->digits.pop_back();
        }
        if (this->digits.size() == 1 && this->digits[0] == 0) {
            this->isNeg = false;
        }
    }

    /// Конструктор
    /// \param str Строка
    explicit LongAr(string str) {
        if (str[0] == '-') {
            str = str.substr(1);
            this->isNeg = true;
        } else {
            this->isNeg = false;
        }
        for (auto i = static_cast<long long>(str.length()); i > 0; i--) {
            this->digits.push_back((short int) stoi(str.substr(i - 1, 1)));
        }
        this->RemoveZeroes();
    }

    // Конструкторы из целочисленных типов
    explicit LongAr(signed short s) : LongAr(to_string(s)) {}

    explicit LongAr(unsigned short s) : LongAr(to_string(s)) {}

    explicit LongAr(signed int s) : LongAr(to_string(s)) {}

    explicit LongAr(unsigned int s) : LongAr(to_string(s)) {}

    explicit LongAr(signed long s) : LongAr(to_string(s)) {}

    explicit LongAr(unsigned long s) : LongAr(to_string(s)) {}

    explicit LongAr(signed long long s) : LongAr(to_string(s)) {}

    explicit LongAr(unsigned long long s) : LongAr(to_string(s)) {}

    /// Преобразование в строку
    string CreateString() {
        if (this->digits.empty()) {
            return "0";
        } else {
            string str;
            if (this->isNeg) {
                str += '-';
            }
            str += to_string(this->digits.back());
            for (auto i = static_cast<long long>(this->digits.size() - 2); i >= 0; --i) {
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

    LongAr operator+() const {
        LongAr copy(*this);
        return copy;
    }

    /// Поразрядное смещение вправо на 1
    void Right() {
        if (this->digits.empty()) {
            this->digits.push_back(0);
            return;
        }
        this->digits.push_back(this->digits[this->digits.size() - 1]);
        for (auto i = static_cast<long long>(this->digits.size() - 2); i > 0; --i) {
            this->digits[i] = this->digits[i - 1];
        }
        this->digits[0] = 0;
    }
};

ostream &operator<<(ostream &os, const LongAr &la) {
    if (la.digits.empty()) {
        os << 0;
    } else {
        if (la.isNeg) {
            os << '-';
        }
        os << la.digits.back();
        for (auto i = static_cast<long long>(la.digits.size() - 2); i >= 0; --i) {
            os << la.digits[i];
        }
    }
    return os;
}

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
            for (auto i = static_cast<long long>(left.digits.size() - 1); i >= 0; --i) {
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

bool operator!=(const LongAr &left, const LongAr &right) {
    return !(left == right);
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
    short int c = 0;
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
    short int c = 0;
    for (long long i = 0; i < right.digits.size() || c != 0; ++i) {
        left.digits[i] -= c + (i < right.digits.size() ? right.digits[i] : 0);
        c = left.digits[i] < 0;
        if (c != 0) left.digits[i] += LongAr::BASE;
    }
    left.RemoveZeroes();
    return left;
}

LongAr operator*(const LongAr &left, const LongAr &right) {
    LongAr result;
    result.digits.resize(left.digits.size() + right.digits.size());
    for (long long i = 0; i < left.digits.size(); ++i) {
        short int c = 0;
        for (long long j = 0; j < right.digits.size() || c != 0; ++j) {
            long long cur = result.digits[i + j] +
                            left.digits[i] * 1LL * (j < right.digits.size() ? right.digits[j] : 0) + c;
            result.digits[i + j] = cur % LongAr::BASE;
            c = cur / LongAr::BASE;
        }
    }
    result.isNeg = left.isNeg != right.isNeg;
    result.RemoveZeroes();
    return result;
}

LongAr operator/(const LongAr &left, const LongAr &right) {
    LongAr b = right;
    b.isNeg = false;
    LongAr result, current;
    result.digits.resize(left.digits.size());
    for (auto i = static_cast<long long>(left.digits.size() - 1); i >= 0; --i) {
        current.Right();
        current.digits[0] = left.digits[i];
        current.RemoveZeroes();
        int x = 0, l = 0, r = LongAr::BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            LongAr t = b * LongAr(m);
            if (t <= current) {
                x = m;
                l = m + 1;
            } else r = m - 1;
        }
        result.digits[i] = x;
        current = current - b * LongAr(x);
    }
    result.isNeg = left.isNeg != right.isNeg;
    result.RemoveZeroes();
    return result;
}

LongAr operator%(const LongAr &left, const LongAr &right) {
    LongAr result = left - (left / right) * right;
    if (result.isNeg) {
        result = result + right;
    }
    return result;
}