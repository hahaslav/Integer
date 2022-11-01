#include "PseudoFloat.h"

// http://www.dsplog.com/2011/12/25/newtons-method-square-root-inverse/

const int ITERATIONS = 2;

std::string inverse(const TInteger &n) {
    int i;
    TInteger x(1), float_shift = pow(I_TEN, n.length());
    TInteger d = n * float_shift, real_two = I_TWO * float_shift;

    for (i = 0; i < ITERATIONS; i++) {
        x = x * (real_two - x * d / float_shift); // TODO make operator/(TInteger)
        d = d * float_shift;
        real_two = real_two * float_shift;
        float_shift = float_shift * float_shift;
    }

    std::string result = "0.";

    for (i = 0; i < float_shift.length() - x.length() - 1; i++) {
        result += "0";
    }
    result += (std::string)x;

    return result;
}