#include "TInteger.h"

#ifndef LAB2_MULTIPLICATION_H
#define LAB2_MULTIPLICATION_H
class Multiplication {
protected:
    static bool negative_after_multiplication(const TInteger &a, const TInteger &b) {
        return a.is_negative() xor b.is_negative();
    }

    static TInteger pow_of_10(const int n) {
        TInteger ten(10), result = ten;
        int i;

        for (i = 2; i <= n; i++) {
            result = result * ten;
        }

        return result;
    }
public:
    virtual TInteger multiply(const TInteger &a, const TInteger &b) const { return TInteger(1); }
};

class Karatsuba: public Multiplication {
public:
    TInteger multiply(const TInteger &a, const TInteger &b) const override;
};

class TomCook: public Multiplication {
public:
    TInteger multiply(const TInteger &a, const TInteger &b) const override;
};

class Modular: public Multiplication {
public:
    TInteger multiply(const TInteger &a, const TInteger &b) const override;
};

class SchonhageShtrassen: public Multiplication {
public:
    TInteger multiply(const TInteger &a, const TInteger &b) const override;
};
#endif //LAB2_MULTIPLICATION_H
