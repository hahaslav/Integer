#include "Multiplication.h"

// https://en.wikipedia.org/wiki/Tom-Cook_multiplication
// base 2 is not required
// efficiency is not required
// make Tom-3

const int TOM = 3;

TInteger TomCook::multiply(TInteger a, TInteger b) {
    if (std::abs((int)a) < BASE * BASE || std::abs((int)b) < BASE * BASE) {
        return a * b;
    }

    bool to_invert = negative_after_multiplication(a, b);

    // splitting
    TInteger longest;
    int split_lenght = std::max(a.length(), b.length());
    if (split_lenght == a.length()) {
        longest = a;
    } else {
        longest = b;
    }
    split_lenght /= TOM;
    if (longest.length() % 3 != 0) {
        split_lenght++;
    }

    std::vector<TInteger> parts_a = a.split(TOM, split_lenght);
    std::vector<TInteger> parts_b = b.split(TOM, split_lenght);

    // evaluation


    // pointwise multiplication


    // interpolation
    /*
     *   /  6 0  0  0  0  \ /  r(0) \
     * 1 |  3 2 -6  1 -12 | |  r(1) |
     * - | -6 3  3  0  -6 | | r(-1) |
     * 6 | -3 1  3 -1  12 | | r(-2) |
     *   \  0 0  0  0  6  / \  r(∞) /
     */


    // recomposition


    return TInteger(59932);
}