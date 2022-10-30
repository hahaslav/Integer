#include "Prime.h"

// https://en.wikipedia.org/wiki/AKS_primality_test

bool is_perfect_power(const TInteger &n) {
    TInteger a = I_TWO, b = I_TWO;

    while (pow(a, I_TWO) <= n) {
        TInteger value = pow(a, b);

        if (value == n) {
            return true;
        }
        if (value > n) {
            a = a + I_ONE;
            b = I_TWO;
        } else {
            b = b + I_ONE;
        }
    }

    return false;
}

TInteger kinda_log2(const TInteger &n) {
    /*
     * Returns ceil of logarithm of n with base 2
     */
    TInteger result = I_ONE;

    while (pow(I_TWO, result) < n) {
        result = result + I_ONE;
    }

    return result;
}

TInteger gcd(const TInteger &a, const TInteger &b) {
    if (a % b == I_ZERO) {
        return b;
    }
    return gcd(b, a % b);
}

bool coprime(const TInteger &a, const TInteger &b) {
    return gcd(a, b) == I_ONE;
}

TInteger ord(const TInteger &a, const TInteger &n) {
    /*
     * Returns multiplicative order of a modulo n
     * https://en.wikipedia.org/wiki/Multiplicative_order
     *
     * Given integers must be coprime
     */
    TInteger result = I_ONE;

    while (pow(a, result, n) != I_ONE) {
        result = result + I_ONE;
    }

    return result;
}

std::string Agrawal::check(const TInteger &a) const {
    std::string fast_result = basic_check(a);
    if (fast_result != "") {
        return fast_result;
    }

    if (is_perfect_power(a)) {
        return NOT_PRIME;
    }

    TInteger r = I_TWO, log2a2 = pow(kinda_log2(a), I_TWO);

    while (true) {
        if (! coprime(a, r)) {
            r = r + I_ONE;
            continue;
        }
        if (ord(a, r) > log2a2) {
            break;
        }
        r = r + I_ONE;
    }

    return (std::string)r;
}