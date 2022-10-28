#include "Prime.h"

// https://en.wikipedia.org/wiki/Fermat_primality_test

std::string Fermat::check(const TInteger &a) const {
    std::string fast_result = basic_check(a);
    if (fast_result != "") {
        return fast_result;
    }

    return "Fermat_idk";
}