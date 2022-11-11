#include "TInteger.h"

#ifndef LAB2_MULTIPLICATION_H
#define LAB2_MULTIPLICATION_H
class Multiplication {
protected:
    static bool negative_after_multiplication(const TInteger &a, const TInteger &b) {
        return a.is_negative() xor b.is_negative();
    }
public:
    virtual TInteger multiply(const TInteger &a, const TInteger &b) const { return I_ONE; }
};

class Karatsuba: public Multiplication {
public:
    TInteger multiply(const TInteger &a, const TInteger &b) const override;
};

class TomCook: public Multiplication {
public:
    TInteger multiply(const TInteger &a, const TInteger &b) const override;
};

class RepeatedAddition: public Multiplication {
public:
    TInteger multiply(const TInteger &a, const TInteger &b) const override;
};
#endif //LAB2_MULTIPLICATION_H
