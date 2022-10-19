#include "TInteger.h"

TInteger::TInteger() {}

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

TInteger::TInteger(std::vector<int> integer) {
    int i;

    for (i = integer.size() - 1; i > 0; i--) {
        if (integer[i] == 0) {
            integer.pop_back();
        } else break;
    }

    digits = integer;
}

void TInteger::invert() {
    negative = not negative;
}

bool TInteger::is_negative() {
    return negative;
}

int TInteger::length() {
    return digits.size();
}

TInteger TInteger::operator+(TInteger other) {
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

TInteger TInteger::operator-(TInteger other) {
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

TInteger TInteger::operator*(TInteger other) {
    TInteger result (0);
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

    if (to_invert) {
        result.invert();
    }
    return result;
}

TInteger TInteger::operator/(int other) {
    /*
     * Returns integer part of division
     */
    bool to_invert = negative xor (other < 0);
    int i = length() - 1, remainder = 0, one_division;
    std::vector<int> reversed_value;

    while (remainder < other && i >= 0) {
        remainder = remainder * BASE + digits[i];
        i--;
    }
    if (remainder < other) {
        return TInteger(0);
    }

    while (i >= 0) {
        one_division = remainder / other;
        reversed_value.push_back(one_division);
        remainder -= one_division * other;

        remainder = remainder * BASE + digits[i];
        i--;
    }
    one_division = remainder / other;
    reversed_value.push_back(one_division);

    std::vector<int> result_value;
    for (i = reversed_value.size() - 1; i >= 0; i--) {
        result_value.push_back(reversed_value[i]);
    }

    TInteger result(result_value);
    if (to_invert) {
        result.invert();
    }
    return result;
}

TInteger::operator std::string() {
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

TInteger::operator int() {
    // if integer's absolute value is bigger than 999'999'999, returns (it's sign)1'000'000'000
    if (length() > 9) {
        return 1'000'000'000 * (-1 * (negative));
    }

    int result = 0, i;

    for (i = length() - 1; i >= 0; i--) {
        result = result * BASE + digits[i];
    }

    if (negative) {
        result *= -1;
    }
    return result;
}

std::vector<TInteger> TInteger::split(int parts, int part_length) {
    /*
     * Returns some parts of the integer, with using given part length
     * Forgets about the integer's sign
     */
    int full_length = part_length * parts;

    if (length() > full_length) throw;

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

std::vector<TInteger> TInteger::halves(int half_length) {
    /*
     * Returns two parts of the integer, with using given part length
     * Forgets about the integer's sign
     */
    return split(2, half_length);
}