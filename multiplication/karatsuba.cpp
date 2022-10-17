#include "Multiplication.h"

// https://en.wikipedia.org/wiki/Karatsuba_algorithm

TInteger pow_of_10(int n) {
    TInteger ten(10), result = ten;
    int i;

    for (i = 2; i <= n; i++) {
        result = result * ten;
    }

    return result;
}

TInteger Karatsuba::multiply(TInteger a, TInteger b) {
    if ((int)a < BASE || (int)b < BASE) {
        return a * b;
    }

    int half_length = std::max(a.length(), b.length());
    half_length += half_length % 2;
    half_length /= 2;

    std::vector<TInteger> a_halves = a.halves(half_length), b_halves = b.halves(half_length);
    TInteger base_m = pow_of_10(half_length), base_2m = pow_of_10(2 * half_length);

    TInteger result = multiply(a_halves[0], b_halves[0]) * base_2m
            + (multiply(a_halves[0], b_halves[1]) + multiply(a_halves[1], b_halves[0])) * base_m
            + multiply(a_halves[1], b_halves[1]);
    return result;
}