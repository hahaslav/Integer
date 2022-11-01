#include "Multiplication.h"

// https://en.wikipedia.org/wiki/Karatsuba_algorithm

TInteger Karatsuba::multiply(const TInteger &a, const TInteger &b) const {
    if (std::abs((int)a) < BASE || std::abs((int)b) < BASE) {
        return a * b;
    }

    bool to_invert = negative_after_multiplication(a, b);

    int half_length = std::max(a.length(), b.length());
    half_length += half_length % 2;
    half_length /= 2;

    std::vector<TInteger> a_halves = a.halves(half_length), b_halves = b.halves(half_length);
    TInteger base_m = pow(I_TEN, half_length), base_2m = pow(I_TEN, 2 * half_length);

    TInteger result = a_halves[0] * b_halves[0] * base_2m
            + (a_halves[0] * b_halves[1] + a_halves[1] * b_halves[0]) * base_m
            + a_halves[1] * b_halves[1];
    if (to_invert) {
        result.invert();
    }

    return result;
}