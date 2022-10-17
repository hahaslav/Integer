#include "TInteger.h"

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
    int i;

    for (i = integer.size() - 1; i > 0; i--) {
        if (integer[i] == 0) {
            integer.pop_back();
        } else break;
    }

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

TInteger TInteger::operator-(TInteger other) {
    // if a - b < 0, then it returns 0 instead
    // because all methods use positive numbers
    if (length() < other.length()) {
        TInteger result(0);
        return result;
    }

    std::vector<int> result_value;
    int i, overflow = 0;

    for (i = 0; i < other.length(); i++) {
        int next = overflow + digits[i] - other.digits[i];
        if (next < 0) {
            overflow = -1;
            next += BASE;
        } else {
            overflow = 0;
        }
        result_value.push_back(next);
    }
    for (; i < length(); i++) {
        int next = overflow + digits[i];
        if (next < 0) {
            overflow = -1;
            next += BASE;
        } else {
            overflow = 0;
        }
        result_value.push_back(next);
    }

    TInteger result;
    if (overflow < 0) {
        result = TInteger(0);
    } else {
        result = TInteger(result_value);
    }
    return result;
}

TInteger TInteger::operator*(TInteger other) {
    TInteger result (0);
    int i, j;

    if (other.length() == 1) {
        int overflow = 0;

        for (i = 0; i < length(); i++) {
            std::vector<int> subvalue(i + 1, 0);
            int subproduct = digits[i] * other.digits[0] + overflow;
            overflow = subproduct / 10;
            subvalue[i] = subproduct % 10;
            result = result + TInteger(subvalue);
        }
        std::vector<int> subvalue(i + 1, 0);
        subvalue[subvalue.size() - 1] = overflow;
        result = result + TInteger(subvalue);

        return result;
    }

    for (i = 0; i < other.length(); i++) {
        TInteger subproduct = *this * TInteger(other.digits[i]);
        std::vector<int> subvalue(subproduct.length() + i, 0);
        for (j = 0; j < subproduct.length(); j++) {
            subvalue[j + i] = subproduct.digits[j];
        }
        result = result + (TInteger(subvalue));
    }

    return result;
}

TInteger::operator std::string() {
    int i;
    std::string result = "";
    for (i = digits.size() - 1; i >= 0; i--) {
        result += digits[i] + '0'; // it is converted to the ASCII character code
    }

    return result;
}

TInteger::operator int() {
    // if integer is bigger than 999'999'999, returns 1'000'000'000
    if (length() > 9) {
        return 1'000'000'000;
    }

    int result = 0, i;

    for (i = length() - 1; i >= 0; i--) {
        result = result * BASE + digits[i];
    }

    return result;
}

std::vector<TInteger> TInteger::halves() {
    if (length() < 2) throw;

    return halves(length());
}

std::vector<TInteger> TInteger::halves(int half_length) {
    /*
     * Returns two halves of the integer, with using given length
     */
    int full_length = half_length * 2;

    if (length() > full_length) throw;

    std::vector<int> result_values1, result_values2;
    int i;

    for (i = 0; i < half_length; i++) {
        result_values2.push_back(digits[i]);
    }
    for (; i < full_length; i++) {
        if (i < length()) {
            result_values1.push_back(digits[i]);
        } else {
            result_values1.push_back(0);
        }
    }

    std::vector<TInteger> result;
    result.push_back(TInteger(result_values1));
    result.push_back(TInteger(result_values2));

    return result;
}