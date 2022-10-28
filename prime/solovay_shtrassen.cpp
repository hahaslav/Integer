#include "Prime.h"

// https://en.wikipedia.org/wiki/Solovay%E2%80%93Strassen_primality_test

std::string SolovayShtrassen::check(const TInteger &a) const {
    std::string fast_result = basic_check(a);
    if (fast_result != "") {
        return fast_result;
    }

    return "SolovayShtrassen_idk";
}