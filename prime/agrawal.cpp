#include "Prime.h"

// TODO: Consider removing this message because you can do it :-)
// Warning! Your brain level is below recommended level
// https://en.wikipedia.org/wiki/AKS_primality_test

std::string Agrawal::check(TInteger a) {
    std::string fast_result = basic_check(a);
    if (fast_result != "") {
        return fast_result;
    }

    return "Agrawal_idk";
}