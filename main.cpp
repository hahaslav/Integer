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
    // 59932
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

    TInteger c("21474836470");

    std::cout << (int)c << "\n";

    std::vector<TInteger> parts = c.split(8, 3);
    for (int i = 0; i < parts.size(); i++) {
        std::cout << parts[i] << ' ';
    }
    std::cout << "\n";

    a = TInteger(256);
    int divider = 5;
    std::cout << a / divider << "\n";

    a = TInteger(26006);
    std::cout << a / divider << "\n";

    a = TInteger(1);
    std::cout << a / divider << "\n";

    return 0;
}