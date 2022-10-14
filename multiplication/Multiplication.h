#include "TInteger.h"

#ifndef LAB2_MULTIPLICATION_H
#define LAB2_MULTIPLICATION_H
class Multiplication {
public:
    virtual TInteger multiply(TInteger a, TInteger b) { return TInteger(1); }
};

class Karatsuba: public Multiplication {
public:
    TInteger multiply(TInteger a, TInteger b) override;
};

class Modular: public Multiplication {
public:
    TInteger multiply(TInteger a, TInteger b) override;
};
#endif //LAB2_MULTIPLICATION_H
