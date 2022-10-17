#include "TInteger.h"

#ifndef LAB2_PRIME_H
#define LAB2_PRIME_H
class PrimalityCheck {
public:
    virtual TInteger check(TInteger a, TInteger b) { return TInteger(1); }
};

class Fermat: public PrimalityCheck {
public:
    TInteger check(TInteger a, TInteger b) override;
};

class RabinMiller: public PrimalityCheck {
public:
    TInteger check(TInteger a, TInteger b) override;
};

class SolovayShtrassen: public PrimalityCheck {
public:
    TInteger check(TInteger a, TInteger b) override;
};

class Agrawal: public PrimalityCheck {
public:
    TInteger check(TInteger a, TInteger b) override;
};

#endif //LAB2_PRIME_H
