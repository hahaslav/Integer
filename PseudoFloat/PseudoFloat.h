#include "TInteger.h"

#ifndef INTEGER_PSEUDOFLOAT_H
#define INTEGER_PSEUDOFLOAT_H
class PseudoFloat: public TInteger {
    using TInteger::TInteger;
    /*
     * Holds a float like 0.x
     * Assumes that the left part
     * from the dot is 0
     */
public:
    operator std::string() const override;
};


#endif //INTEGER_PSEUDOFLOAT_H
