#include "PseudoFloat.h"

// http://www.dsplog.com/2011/12/25/newtons-method-square-root-inverse/

const int ITERATIONS = 10;
const int PRECISION = 20;

std::string inverse(const TInteger &n) {
    int i;
    TInteger x(1), float_shift = pow(I_BASE, n.length());
    TInteger d = n * float_shift, real_two = I_TWO * float_shift;
    if (d.is_negative()) {
        d.invert();
    }

    for (i = 0; i < ITERATIONS; i++) {
        int precision_cut_length = float_shift.length() - PRECISION;
        if (precision_cut_length > 0) {
            TInteger precision_cut = pow(I_BASE, precision_cut_length);
            x = x / precision_cut;
            d = d / precision_cut;
            real_two = real_two / precision_cut;
            float_shift = float_shift / precision_cut;
        }
        x = x * (real_two - x * d / float_shift);
        d = d * float_shift;
        real_two = real_two * float_shift;
        float_shift = float_shift * float_shift;
    }

    std::string result = "";
    if (n.is_negative()){
        result += "-";
    }
    result += "0.";

    for (i = 0; i < float_shift.length() - x.length() - 1; i++) {
        result += "0";
    }
    result += (std::string)x;

    return result;
}