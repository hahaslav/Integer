#include <iostream>

#include "multiplication/Multiplication.h"

#include "cook/float_cook.h"
#include "cook/division_cook.h"

#include "prime/Prime.h"

std::ostream &operator<<(std::ostream &output, TInteger a) {
    return output << (std::string)a;
}

int main() {
    TInteger a(123), b("456");

    // Should output:
    // 56088
    // 56088
    // 54321
    // 33141
    //
    // *output for the next tests*

    // It means, that all methods have been used

    Multiplication* multiply_method = new Karatsuba;
    std::cout << multiply_method->multiply(a, b) << "\n";

    multiply_method = new TomCook;
    std::cout << multiply_method->multiply(a, b) << "\n";

    multiply_method = new Modular;
    std::cout << multiply_method->multiply(a, b) << "\n";

    multiply_method = new SchonhageShtrassen;
    std::cout << multiply_method->multiply(a, b) << "\n\n";

    std::cout << a * b << "\n"; // 123 * 456 = 56088

    a = TInteger(4);
    b = TInteger(0);

    try {
        std::cout << a / b << " " << a % b << "\n";
    } catch (char const* msg) {
        std::cout << msg << "\n";
    }

    return 0;
}