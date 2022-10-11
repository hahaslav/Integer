#include <vector>
#include <string>

#ifndef LAB2_TINTEGER_H
#define LAB2_TINTEGER_H
class TInteger {
    /*
     * Holds an integer of a large length
     *
     * Arithmetical operations are done
     * in a classic school way "in column"
     */
    std::vector<int> digits;
public:
    TInteger();

    TInteger(int integer);

    TInteger(std::string integer);

    std::string to_string();
};
#endif //LAB2_TINTEGER_H
