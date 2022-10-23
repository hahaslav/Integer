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
    bool negative = false;

    std::vector<TInteger> integer_division(int b);
public:
    TInteger();

    TInteger(int integer);

    TInteger(std::string integer);

    TInteger(std::vector<int> integer);

    void invert();

    bool is_negative();

    int length();

    TInteger operator+(TInteger other);

    TInteger operator-(TInteger other);

    TInteger operator*(TInteger other);

    TInteger operator/(int other);

    TInteger operator%(int other);

    operator std::string();

    operator int();

    std::vector<TInteger> split(int parts, int part_length);

    std::vector<TInteger> halves(int half_length);
};
#endif //LAB2_TINTEGER_H
