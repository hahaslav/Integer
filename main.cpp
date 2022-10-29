#include <iostream>

#include "multiplication/Multiplication.h"

#include "cook/float_cook.h"
#include "cook/division_cook.h"

#include "prime/Prime.h"

std::ostream &operator<<(std::ostream &output, const TInteger &a) {
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

    TInteger pa(222), pb(223), pc(1111);
    TInteger na(-222), nb(-223), nc(-1111);

    std::cout << (pa > pb) << ' ' << (pa > pc) << ' ' << (na > nb) << ' ' << (na > nc) << ' ' << (pa > na) << ' ' << (na > pa) << "\n";
    std::cout << (pa < pb) << ' ' << (pa < pc) << ' ' << (na < nb) << ' ' << (na < nc) << ' ' << (pa < na) << ' ' << (na < pa) << "\n";
    std::cout << (pa > pa) << ' ' << (pa >= pa) << ' ' << (na > na) << ' ' << (na >= na) << "\n";
    std::cout << (pa < pa) << ' ' << (pa <= pa) << ' ' << (na < na) << ' ' << (na <= na) << "\n";
    std::cout << (I_ZERO < pa) << ' ' << (I_ZERO < na) << ' ' << (I_ZERO > pa) << ' ' << (I_ZERO > na) << "\n";
    std::cout << (I_ZERO < I_ONE) << ' ' << (I_ZERO < TInteger(-1)) << ' ' << (I_ZERO > I_ONE) << ' ' << (I_ZERO > TInteger(-1)) << "\n";

    TInteger prime(6323);

    PrimalityCheck* is_prime = new Fermat;
    std::cout << is_prime->check(prime) << "\n";

    is_prime = new RabinMiller;
    std::cout << is_prime->check(prime) << "\n";

    is_prime = new SolovayShtrassen;
    std::cout << is_prime->check(prime) << "\n";

    return 0;
}