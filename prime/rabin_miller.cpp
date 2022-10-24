#include "Prime.h"

// https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test

const int BASES = 4;
const int MAX_INTEGER = 999'999'997;
const TInteger ZERO(0);
const TInteger ONE(1);

std::string RabinMiller::check(TInteger a) {
    std::string fast_result = basic_check(a);
    if (fast_result != "") {
        return fast_result;
    }

    srand(time(0));
    TInteger d = a / TInteger(2);
    int s = 0;
    std::vector<TInteger> better_d = d.integer_division(2);
    while (better_d[1] == ZERO) {
        d = better_d[0];
        s++;
        better_d = d.integer_division(2);
    }

    int i, k, max_base = std::min(MAX_INTEGER, (int)(a - TInteger(4)));
    TInteger j;

    for (i = 0; i < BASES; i++) {
        TInteger base(rand() % max_base + 2);

        TInteger x(1);
        for (j = ZERO; j != d; j = j + ONE) {
            x = x * base % a;
        }

        if (x == ONE || x == a - ONE) {
            continue;
        }

        bool f = false;
        for (k = 0; k < s; k++) {
            x = x * x % a;
            if (x == a - ONE) {
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