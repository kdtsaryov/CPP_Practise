#include <string>
#include <utility>
#include <vector>
#include <cctype>
#include <cstring>
#include <stdexcept>

using namespace std;

/// Одно выражение (унарное, бинарное или число)
struct Expression {
    // Операция или число
    string token;
    // Аргументы
    vector<Expression> args;

    /// Конструктор для числа
    explicit Expression(string token) : token(move(token)) {}
    /// Конструктор для унарного
    Expression(string token, Expression a) : token(move(token)), args{ move(a) } {}
    /// Конструктор для бинарного
    Expression(string token, Expression a, Expression b) : token(move(token)), args{ move(a), move(b) } {}
};

/// Класс парсера математического выражения
class Parser {
private:
    // Входная строка
    const char* input;

    /// Парсер одного токена
    string ParseToken() {
        while (isspace(*input)) ++input;
        if (isdigit(*input)) {
            string number;
            while (isdigit(*input)) number.push_back(*input++);
            return number;
        }
        static const string tokens[] =
                { "+", "-", "*", "/", "%", "(", ")" };
        for (auto& t : tokens) {
            if (strncmp(input, t.c_str(), t.size()) == 0) {
                input += t.size();
                return t;
            }
        }
        return "";
    }

    /// Парсер простого выражения
    Expression ParseSimple() {
        auto token = ParseToken();
        if (token.empty()) throw runtime_error("Invalid input");
        if (token == "(") {
            auto result = Parse();
            if (ParseToken() != ")") throw runtime_error("Expected ')'");
            return result;
        }
        if (isdigit(token[0]))
            return Expression(token);
        return {token, ParseSimple()};
    }

    /// Приоритеты операций
    static int Priority(const string& op) {
        if (op == "+") return 1;
        if (op == "-") return 1;
        if (op == "*") return 2;
        if (op == "/") return 2;
        if (op == "%") return 2;
        return 0;
    }

    /// Парсер бинарного выражения
    Expression ParseBinary(int min) {
        auto left = ParseSimple();
        for (;;) {
            auto op = ParseToken();
            auto priority = Priority(op);
            if (priority <= min) {
                input -= op.size();
                return left;
            }
            auto right = ParseBinary(priority);
            left = Expression(op, left, right);
        }
    }

public:
    explicit Parser(const char* input) : input(input) {}

    Expression Parse() {
        return ParseBinary(0);
    }

    /// Вычисляет значение введенного выражения
    LongAr Calculate(const Expression& e) {
        switch (e.args.size()) {
            case 2: {
                auto a = Calculate(e.args[0]);
                auto b = Calculate(e.args[1]);
                if (e.token == "+") return a + b;
                if (e.token == "-") return a - b;
                if (e.token == "*") return a * b;
                if (e.token == "/") return a / b;
                if (e.token == "%") return a % b;
                throw runtime_error("Unknown binary operator");
            }
            case 1: {
                auto a = Calculate(e.args[0]);
                if (e.token == "+") return +a;
                if (e.token == "-") return -a;
                throw runtime_error("Unknown unary operator");
            }
            case 0:
                return LongAr(e.token);
        }
        return {};
    }
};