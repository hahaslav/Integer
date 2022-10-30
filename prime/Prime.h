#include "TInteger.h"

#ifndef LAB2_PRIME_H
#define LAB2_PRIME_H
const std::string IS_PRIME = "IS_PRIME";
const std::string NOT_PRIME = "NOT_PRIME";
const int MAX_RND_INTEGER = 999'999'997;

class PrimalityCheck {
protected:
    static std::string basic_check(const TInteger &a) {
            if ((a == I_TWO) ||
                (a == TInteger(3)) ||
                (a == TInteger(5)) ||
                (a == TInteger(7)) ||
                (a == TInteger(11)) ||
                (a == TInteger(13)) ||
                (a == TInteger(17)) ||
                (a == TInteger(19))) {
                return IS_PRIME;
            }
            if ((a == I_ZERO) || (a == I_ONE) || (a.is_negative()) ||
                (a % I_TWO == I_ZERO) ||
                (a % TInteger(3) == I_ZERO) ||
                (a % TInteger(5) == I_ZERO) ||
                (a % TInteger(7) == I_ZERO) ||
                (a % TInteger(11) == I_ZERO) ||
                (a % TInteger(13) == I_ZERO) ||
                (a % TInteger(17) == I_ZERO) ||
                (a % TInteger(19) == I_ZERO)) {
                return NOT_PRIME;
            }
        return "";
    }
public:
    virtual std::string check(const TInteger &a) const { return "Choose a child class"; }
};

class Fermat: public PrimalityCheck {
public:
    std::string check(const TInteger &a) const override;
};

class RabinMiller: public PrimalityCheck {
public:
    std::string check(const TInteger &a) const override;
};

class SolovayStrassen: public PrimalityCheck {
public:
    std::string check(const TInteger &a) const override;
};

class Agrawal: public PrimalityCheck {
public:
    std::string check(const TInteger &a) const override;
};

#endif //LAB2_PRIME_H
