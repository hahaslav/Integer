#include "TInteger.h"

#ifndef LAB2_MULTIPLICATION_H
#define LAB2_MULTIPLICATION_H
class Multiplication {
protected:
    bool negative_after_multiplication(TInteger a, TInteger b) {
        return a.is_negative() xor b.is_negative();
    }

    TInteger pow_of_10(int n) {
        TInteger ten(10), result = ten;
        int i;

        for (i = 2; i <= n; i++) {
            result = result * ten;
        }

        return result;
    }
public:
    virtual TInteger multiply(TInteger a, TInteger b) { return TInteger(1); }
};

class Karatsuba: public Multiplication {
public:
    TInteger multiply(TInteger a, TInteger b) override;
};

class TomCook: public Multiplication {
public:
    TInteger multiply(TInteger a, TInteger b) override;
};

class Modular: public Multiplication {
public:
    TInteger multiply(TInteger a, TInteger b) override;
};

class SchonhageShtrassen: public Multiplication {
public:
    TInteger multiply(TInteger a, TInteger b) override;
};
#endif //LAB2_MULTIPLICATION_H
