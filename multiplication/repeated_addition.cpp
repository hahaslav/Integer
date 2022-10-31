#include "Multiplication.h"

// As it is said, multiplication is repeated addition
// https://en.wikipedia.org/wiki/Multiplication

TInteger RepeatedAddition::multiply(const TInteger &a, const TInteger &b) const {
    TInteger i, result = I_ZERO;

    bool to_invert = negative_after_multiplication(a, b);

    for (i = I_ZERO; i != b; i = i + I_ONE) {
        result = result + a;
    }

    if (to_invert) {
        result.invert();
    }
    return result;
}