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

std::string Agrawal::check(const TInteger &a) const {
    std::string fast_result = basic_check(a);
    if (fast_result != "") {
        return fast_result;
    }

    if (is_perfect_power(a)) {
        return NOT_PRIME;
    }

    return "Agrawal_idk";
}