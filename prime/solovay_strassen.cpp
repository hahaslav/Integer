#include "Prime.h"

// https://en.wikipedia.org/wiki/Solovay%E2%80%93Strassen_primality_test

const int TESTS = 4;

std::string SolovayStrassen::check(const TInteger &a) const {
    std::string fast_result = basic_check(a);
    if (fast_result != "") {
        return fast_result;
    }

    srand(time(0));
    TInteger p = a - I_ONE;
    TInteger n = p / TInteger(2);
    int i;

    for (i = 0; i < TESTS; i++) {
        TInteger base(rand() % MAX_RND_INTEGER + 2);
        TInteger x = pow(base, n, a);

        if (x == I_ONE || x == I_ZERO || x == p) {
            continue;
        }

        return NOT_PRIME;
    }

    return IS_PRIME;

}