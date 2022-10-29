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
public:
    TInteger();

    TInteger(int integer);

    TInteger(std::string integer);

    TInteger(std::vector<int> integer);

    void invert();

    bool is_negative() const;

    int length() const;

    TInteger operator+(const TInteger &other) const;

    TInteger operator-(const TInteger &other) const;

    TInteger operator*(const TInteger &other) const;

    std::vector<TInteger> integer_division(const int other) const;

    TInteger operator/(const int other) const;

    TInteger operator%(const int other) const;

    bool operator==(const TInteger &other) const;

    bool operator!=(const TInteger &other) const;

    operator std::string() const;

    operator int() const;

    std::vector<TInteger> split(int parts, int part_length) const;

    std::vector<TInteger> halves(int half_length) const;
};

const TInteger I_ZERO(0);
const TInteger I_ONE(1);
#endif //LAB2_TINTEGER_H
