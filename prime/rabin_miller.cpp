#include "Prime.h"

// https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test

const int BASES = 4;

std::string RabinMiller::check(const TInteger &a) const {
    std::string fast_result = basic_check(a);
    if (fast_result != "") {
        return fast_result;
    }

    srand(time(0));
    TInteger d = a / I_TWO;
    int s = 0;
    std::vector<TInteger> better_d = d.integer_division(2);
    while (better_d[1] == I_ZERO) {
        d = better_d[0];
        s++;
        better_d = d.integer_division(2);
    }

    int i, k, max_base = std::min(MAX_RND_INTEGER, (int)(a - TInteger(4)));

    for (i = 0; i < BASES; i++) {
        TInteger base(rand() % max_base + 2);
        TInteger x = pow(base, d, a);

        if (x == I_ONE || x == a - I_ONE) {
            continue;
        }

        bool f = false;
        for (k = 0; k < s; k++) {
            x = x * x % a;
            if (x == a - I_ONE) {
                f = true;
                break;
            }
        }
        if (f) {
            continue;
        }

        return NOT_PRIME;
    }

    return IS_PRIME;
}