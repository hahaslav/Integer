#include <iostream>

#include "multiplication/Multiplication.h"
#include "PseudoFloat/PseudoFloat.h"
#include "prime/Prime.h"

std::ostream &operator<<(std::ostream &output, const TInteger &a) {
    return output << (std::string)a;
}

int main() {
    TInteger a(123), b("456");

    std::cout << inverse(a) << "\n\n";

    // Should output:
    // 56088
    // 56088
    // 54321
    // 33141
    // 56088
    //
    // *output for the next tests*

    // It means, that all methods have been used

    Multiplication* multiply_method = new Karatsuba;
    std::cout << multiply_method->multiply(a, b) << "\n";

    multiply_method = new TomCook;
    std::cout << multiply_method->multiply(a, b) << "\n";

    multiply_method = new Modular;
    std::cout << multiply_method->multiply(a, b) << "\n";

    multiply_method = new SchonhageStrassen;
    std::cout << multiply_method->multiply(a, b) << "\n";

    multiply_method = new RepeatedAddition;
    std::cout << multiply_method->multiply(a, b) << "\n\n";

    std::cout << a * b << "\n"; // 123 * 456 = 56088

    TInteger prime(6323);

    PrimalityCheck* is_prime = new Fermat;
    std::cout << is_prime->check(prime) << "\n";

    is_prime = new RabinMiller;
    std::cout << is_prime->check(prime) << "\n";

    is_prime = new SolovayStrassen;
    std::cout << is_prime->check(prime) << "\n";

    is_prime = new Agrawal;
    std::cout << is_prime->check(1369) << "\n";
    std::cout << is_prime->check(31) << "\n";
    std::cout << is_prime->check(29) << "\n";

    return 0;
}