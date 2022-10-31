#include "Multiplication.h"

// As it is said, multiplication is repeated addition
// https://en.wikipedia.org/wiki/Multiplication

TInteger RepeatedAddition::multiply(const TInteger &a, const TInteger &b) const {
    TInteger i, result = I_ZERO, multiplier = a, multiplicand = b;

    bool to_invert = negative_after_multiplication(a, b);

    if (multiplier < I_ZERO) {
        multiplier.invert();
    }
    if (multiplicand < I_ZERO) {
        multiplicand.invert();
    }

    for (i = I_ZERO; i != multiplicand; i = i + I_ONE) {
        result = result + multiplier;
    }

    if (to_invert) {
        result.invert();
    }
    return result;
}