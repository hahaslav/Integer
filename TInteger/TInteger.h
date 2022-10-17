#include <vector>
#include <string>

#ifndef LAB2_TINTEGER_H
#define LAB2_TINTEGER_H
const int BASE = 10;

class TInteger {
    /*
     * Holds an integer of a large length
     *
     * Arithmetical operations are done
     * in a classic school way "in column"
     */
    std::vector<int> digits; // Index 0 points to the right end of the integer
public:
    TInteger();

    TInteger(int integer);

    TInteger(std::string integer);

    TInteger(std::vector<int> integer);

    int length();

    TInteger operator+(TInteger other);

    TInteger operator-(TInteger other);

    TInteger operator*(TInteger other);

    operator std::string();

    std::vector<TInteger> halves();
};
#endif //LAB2_TINTEGER_H
