#include "Multiplication.h"

// https://en.wikipedia.org/wiki/Tom-Cook_multiplication
// base 2 is not required
// efficiency is not required
// make Tom-3

const int TOM = 3;

std::vector<TInteger> get_p(std::vector<TInteger> m) {
    /*
     * Gets splitted integer
     * Returns vector of p values in the order:
     * p(0), p(1), p(-1), p(-2), p(∞)
     *  [0],  [1], ...
     */
    std::vector<TInteger> result;

    result.push_back(m[2]);
    result.push_back(m[2] + m[1] + m[0]);
    result.push_back(m[2] - m[1] + m[0]);
    result.push_back(m[2] - (TInteger(2) * m[1]) + (TInteger(4) * m[0]));
    result.push_back(m[0]);

    return result;
}

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
    TInteger base_i = pow_of_10(split_lenght);

    // evaluation
    std::vector<TInteger> p_a = get_p(parts_a);
    std::vector<TInteger> p_b = get_p(parts_b);


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