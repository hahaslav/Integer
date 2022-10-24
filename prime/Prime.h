#include "TInteger.h"

#ifndef LAB2_PRIME_H
#define LAB2_PRIME_H
const std::string IS_PRIME = "IS_PRIME";
const std::string NOT_PRIME = "NOT_PRIME";

class PrimalityCheck {
protected:
    std::string basic_check(TInteger a) {
            if ((a == TInteger(2)) ||
                (a == TInteger(3)) ||
                (a == TInteger(5)) ||
                (a == TInteger(7)) ||
                (a == TInteger(11)) ||
                (a == TInteger(13)) ||
                (a == TInteger(17)) ||
                (a == TInteger(19))) {
                return IS_PRIME;
            }
            if ((a == TInteger(0)) || (a == TInteger(1)) || (a.is_negative()) ||
                (a % TInteger(2) == TInteger(0)) ||
                (a % TInteger(3) == TInteger(0)) ||
                (a % TInteger(5) == TInteger(0)) ||
                (a % TInteger(7) == TInteger(0)) ||
                (a % TInteger(11) == TInteger(0)) ||
                (a % TInteger(13) == TInteger(0)) ||
                (a % TInteger(17) == TInteger(0)) ||
                (a % TInteger(19) == TInteger(0))) {
                return NOT_PRIME;
            }
        return "";
    }
public:
    virtual TInteger check(TInteger a) { return TInteger(1); }
};

class Fermat: public PrimalityCheck {
public:
    TInteger check(TInteger a) override;
};

class RabinMiller: public PrimalityCheck {
public:
    TInteger check(TInteger a) override;
};

class SolovayShtrassen: public PrimalityCheck {
public:
    TInteger check(TInteger a) override;
};

class Agrawal: public PrimalityCheck {
public:
    TInteger check(TInteger a) override;
};

#endif //LAB2_PRIME_H
