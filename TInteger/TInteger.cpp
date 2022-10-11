#include "TInteger.h"

const int BASE = 10;

TInteger::TInteger() {}

TInteger::TInteger(int integer) {
    if (integer == 0) {
        digits.push_back(0);
    } else {
        while (integer > 0) {
            digits.push_back(integer % BASE);
            integer /= BASE;
        }
    }
}

TInteger::TInteger(std::string integer) {
    int i;
    for (i = integer.length() - 1; i >= 0; i--) {
        digits.push_back(integer[i] - '0'); // it is converted from the ASCII character code
    }
}

TInteger::TInteger(std::vector<int> integer) {
    digits = integer;
}

int TInteger::length() {
    return digits.size();
}

TInteger TInteger::operator+(TInteger other) {
    std::vector<int> result_value;
    int i, overflow = 0;
    TInteger a, b;

    if (length() >= other.length()) {
        a = *this;
        b = other;
    } else {
        a = other;
        b = *this;
    }

    for (i = 0; i < b.length(); i++) {
        int next = overflow + a.digits[i] + b.digits[i];
        overflow = next / BASE;
        result_value.push_back(next % 10);
    }
    for (; i < a.length(); i++) {
        int next = overflow + a.digits[i];
        overflow = next / BASE;
        result_value.push_back(next % 10);
    }
    if (overflow > 0) {
        result_value.push_back(overflow);
    }

    TInteger result(result_value);
    return result;
}

std::string TInteger::to_string() {
    int i;
    std::string result = "";
    for (i = digits.size() - 1; i >= 0; i--) {
        result += digits[i] + '0'; // it is converted to the ASCII character code
    }

    return result;
}