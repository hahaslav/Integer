#include "Prime.h"

// https://en.wikipedia.org/wiki/Fermat_primality_test

const int TESTS = 2;

std::string Fermat::check(const TInteger &a) const {
    std::string fast_result = basic_check(a);
    if (fast_result != "") {
        return fast_result;
    }

    srand(time(0));
    TInteger p = a - I_ONE;
    TInteger j;
    int i;

    for (i = 0; i < TESTS; i++) {
        TInteger base(rand() % MAX_RND_INTEGER + 2);

        TInteger x(1);
        for (j = I_ZERO; j != p; j = j + I_ONE) {
            x = x * base % a;
        }

        if (x == I_ONE) {
            continue;
        }

        return NOT_PRIME;
    }

    return IS_PRIME;
}