#include "TInteger.h"

TInteger::TInteger() {}

TInteger::TInteger(int integer) {
    if (integer == 0) {
        digits.push_back(0);
    } else {
        while (integer > 0) {
            digits.push_back(integer % 10);
            integer /= 10;
        }
    }
}

TInteger::TInteger(std::string integer) {
    int i;
    for (i = integer.length() - 1; i >= 0; i--) {
        digits.push_back(integer[i] - '0'); // it is converted from the ASCII character code
    }
}

std::string TInteger::to_string() {
    int i;
    std::string result = "";
    for (i = digits.size() - 1; i >= 0; i--) {
        result += digits[i] + '0'; // it is converted to the ASCII character code
    }

    return result;
}