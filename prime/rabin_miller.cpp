#include "Prime.h"

// https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test

std::string RabinMiller::check(TInteger a) {
    std::string fast_result = basic_check(a);
    if (fast_result != "") {
        return fast_result;
    }

    return "RabinMiller_idk";
}