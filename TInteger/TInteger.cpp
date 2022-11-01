#include "TInteger.h"

std::vector<TInteger> TInteger::tinteger_division(const TInteger &other) const {
    if (other == I_ZERO) {
        throw("Division by 0");
    }

    std::vector<TInteger> result = {I_ZERO, I_ZERO};
    bool to_invert = negative xor other.negative;

    TInteger b = other;
    if (b.negative) {
        b.invert();
    }

    int i = length() - 1;
    TInteger remainder = I_ZERO, one_division;
    std::vector<TInteger> reversed_value;

    while (remainder < b && i >= 0) {
        remainder = remainder * I_TEN + TInteger(digits[i]);
        i--;
    }
    if (remainder < b) {
        result[1] = remainder;
        return result;
    }

    while (i >= 0) {
        one_division = remainder / b;
        reversed_value.push_back(one_division);
        remainder = remainder - one_division * b;

        remainder = remainder * I_TEN + TInteger(digits[i]);
        i--;
    }
    one_division = remainder / b;
    reversed_value.push_back(one_division);
    remainder = remainder - one_division * b;

    std::vector<int> result_value;
    for (i = reversed_value.size() - 1; i >= 0; i--) {
        result_value.push_back((int)reversed_value[i]);
    }

    result[0] = result_value;
    if (to_invert) {
        result[0].invert();
    }
    result[1] = remainder;
    return result;
}

std::vector<TInteger> TInteger::integer_division(const int other) const {
    if (other == 0) {
        throw("Division by 0");
    }

    std::vector<TInteger> result = {I_ZERO, I_ZERO};
    bool to_invert = negative xor (other < 0);
    int b = std::abs(other);

    int i = length() - 1, remainder = 0, one_division;
    std::vector<int> reversed_value;

    while (remainder < b && i >= 0) {
        remainder = remainder * BASE + digits[i];
        i--;
    }
    if (remainder < b) {
        result[1] = TInteger(remainder);
        return result;
    }

    while (i >= 0) {
        one_division = remainder / b;
        reversed_value.push_back(one_division);
        remainder -= one_division * b;

        remainder = remainder * BASE + digits[i];
        i--;
    }
    one_division = remainder / b;
    reversed_value.push_back(one_division);
    remainder -= one_division * b;

    std::vector<int> result_value;
    for (i = reversed_value.size() - 1; i >= 0; i--) {
        result_value.push_back(reversed_value[i]);
    }

    result[0] = TInteger(result_value);
    if (to_invert) {
        result[0].invert();
    }
    result[1] = TInteger(remainder);
    return result;
}

TInteger::TInteger() {} // for declaration

TInteger::TInteger(int integer) {
    if (integer == 0) {
        digits.push_back(0);
    } else {
        if (integer < 0) {
            invert();
            integer *= -1;
        }
        while (integer > 0) {
            digits.push_back(integer % BASE);
            integer /= BASE;
        }
    }
}

TInteger::TInteger(std::string integer) {
    int i, last = 0;

    if (integer[0] == '-') {
        last++;
        invert();
    }

    for (i = integer.length() - 1; i >= last; i--) {
        digits.push_back(integer[i] - '0'); // it is converted from the ASCII character code
    }
}

TInteger::TInteger(std::vector<int> integer, bool is_negative) {
    int i;

    for (i = integer.size() - 1; i > 0; i--) {
        if (integer[i] == 0) {
            integer.pop_back();
        } else break;
    }

    digits = integer;
    if (is_negative) {
        invert();
    }
}

void TInteger::invert() {
    negative = not negative;
}

bool TInteger::is_negative() const {
    return negative;
}

int TInteger::length() const {
    return digits.size();
}

TInteger TInteger::operator+(const TInteger &other) const {
    std::vector<int> result_value;
    int i, overflow = 0;
    TInteger a = *this;
    TInteger b = other;

    bool to_invert = false;
    if (negative && other.negative) {
        to_invert = true;

    } else if (other.negative) {
        b.invert();
        return a - b;

    } else if (negative) {
        a.invert();
        return b - a;
    }

    if (length() < other.length()) {
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
    if (to_invert) {
        result.invert();
    }
    return result;
}

TInteger TInteger::operator-(const TInteger &other) const {
    std::vector<int> result_value;
    int i, overflow = 0;
    TInteger a = *this;
    TInteger b = other;
    TInteger result;

    if (negative && other.negative) {
        a.invert();
        b.invert();
        return b - a;

    } else if (other.negative) {
        b.invert();
        return a + b;

    } else if (negative) {
        a.invert();
        result = a + b;
        result.invert();
        return result;
    }

    if (a.length() < b.length()) {
        result = b - a;
        result.invert();
        return result;
    }

    for (i = 0; i < other.length(); i++) {
        int next = overflow + a.digits[i] - b.digits[i];
        if (next < 0) {
            overflow = -1;
            next += BASE;
        } else {
            overflow = 0;
        }
        result_value.push_back(next);
    }
    for (; i < length(); i++) {
        int next = overflow + a.digits[i];
        if (next < 0) {
            overflow = -1;
            next += BASE;
        } else {
            overflow = 0;
        }
        result_value.push_back(next);
    }

    if (overflow < 0) {
        result = b - a;
        result.invert();
    } else {
        result = TInteger(result_value);
    }
    return result;
}

TInteger TInteger::operator*(const TInteger &other) const {
    TInteger result = I_ZERO;
    bool to_invert = negative xor other.negative;
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

    } else {
        for (i = 0; i < other.length(); i++) {
            TInteger subproduct = *this * TInteger(other.digits[i]);
            std::vector<int> subvalue(subproduct.length() + i, 0);
            for (j = 0; j < subproduct.length(); j++) {
                subvalue[j + i] = subproduct.digits[j];
            }
            result = result + (TInteger(subvalue));
        }
    }
    if (to_invert) {
        result.invert();
    }
    return result;
}

TInteger TInteger::operator/(const TInteger &other) const {
    /*
     * Returns integer part of division
     */
    return tinteger_division(other)[0];
}

TInteger TInteger::operator/(const int other) const {
    /*
     * Returns integer part of division
     */
    return *this / TInteger(other);
}

TInteger TInteger::operator%(const TInteger &other) const {
    /*
     * Returns remainder of division
     */
    return tinteger_division(other)[1];
}

TInteger TInteger::operator%(const int other) const {
    /*
     * Returns integer part of division
     */
    return *this % TInteger(other);
}

bool TInteger::operator==(const TInteger &other) const {
    return negative == other.negative && digits == other.digits;
}

bool TInteger::operator!=(const TInteger &other) const {
    return negative != other.negative || digits != other.digits;
}

bool TInteger::operator>(const TInteger &other) const {
    if (*this == other) {
        return false;
    }
    if (! negative && other.negative) {
        return true;
    }
    if (negative && ! other.negative) {
        return false;
    }
    if (negative && other.negative) {
        TInteger a = *this;
        TInteger b = other;
        a.invert();
        b.invert();

        return b > a;
    }
    if (length() > other.length()){
        return true;
    }
    if (length() < other.length()){
        return false;
    }
    int i;

    for (i = length() - 1; i >= 0; i--) {
        if (digits[i] > other.digits[i]) {
            return true;
        }
        if (digits[i] < other.digits[i]) {
            return false;
        }
    }

    return false; // they are equal, but it is checked at the beginning
}

bool TInteger::operator>=(const TInteger &other) const {
    return *this == other || *this > other;
}

bool TInteger::operator<(const TInteger &other) const {
    if (*this == other) {
        return false;
    }
    if (! negative && other.negative) {
        return false;
    }
    if (negative && ! other.negative) {
        return true;
    }
    if (negative && other.negative) {
        return other > *this;
    }
    if (length() < other.length()){
        return true;
    }
    if (length() > other.length()){
        return false;
    }
    int i;

    for (i = length() - 1; i >= 0; i--) {
        if (digits[i] < other.digits[i]) {
            return true;
        }
        if (digits[i] > other.digits[i]) {
            return false;
        }
    }

    return false; // they are equal, but it is checked at the beginning
}

bool TInteger::operator<=(const TInteger &other) const {
    return *this == other || *this < other;
}

TInteger::operator std::string() const {
    int i;
    std::string result = "";
    if (negative) {
        result = "-";
    }
    for (i = length() - 1; i >= 0; i--) {
        result += digits[i] + '0'; // it is converted to the ASCII character code
    }

    return result;
}

TInteger::operator int() const {
    // if integer's absolute value is bigger than 999'999'999, returns (it's sign)1'000'000'000
    int result = 0;

    if (length() > 9) {
        result = 1'000'000'000;
        if (negative) {
            result *= -1;
        }
        return result;
    }
    int i;

    for (i = length() - 1; i >= 0; i--) {
        result = result * BASE + digits[i];
    }

    if (negative) {
        result *= -1;
    }

    return result;
}

std::vector<TInteger> TInteger::split(int parts, int part_length) const {
    /*
     * Returns some parts of the integer, with using given part length
     * Forgets about the integer's sign
     */
    int full_length = part_length * parts;

    if (length() > full_length) throw("Integer cannot be splitted fully");

    std::vector<std::vector<int>> result_values;
    int i, j = -1;

    for (i = 0; i < full_length; i++) {
        if (i % part_length == 0) {
            j++;
            std::vector<int> tmp;
            result_values.push_back(tmp);
        }
        if (i < length()) {
            result_values[j].push_back(digits[i]);
        } else {
            result_values[j].push_back(0);
        }
    }

    std::vector<TInteger> result;
    for (i = result_values.size() - 1; i >= 0; i--) {
        result.push_back(TInteger(result_values[i]));
    }
    return result;
}

std::vector<TInteger> TInteger::halves(int half_length) const {
    /*
     * Returns two parts of the integer, with using given part length
     * Forgets about the integer's sign
     */
    return split(2, half_length);
}

TInteger pow(const TInteger &base, const TInteger &exp) {
    /*
     * Returns base^exp
     */
    TInteger result = I_ONE;
    TInteger i;

    for (i = I_ZERO; i != exp; i = i + I_ONE) {
        result = result * base;
    }

    return result;
}

TInteger pow(const TInteger &base, const int exp) {
    /*
     * Returns base^exp
     */
    TInteger result = I_ONE;
    int i;

    for (i = 0; i < exp; i++) {
        result = result * base;
    }

    return result;
}

TInteger pow(const TInteger &base, const TInteger &exp, const TInteger &mod) {
    /*
     * Returns base^exp % mod
     */
    TInteger result = I_ONE;
    TInteger i;

    for (i = I_ZERO; i != exp; i = i + I_ONE) {
        result = result * base % mod;
    }

    return result;
}

TInteger min(const TInteger &a, const TInteger &b) {
    if (a <= b) {
        return a;
    }

    return b;
}