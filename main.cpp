#include <iostream>

#include "multiplication/Multiplication.h"

#include "cook/float_cook.h"
#include "cook/division_cook.h"

#include "prime/fermat.h"
#include "prime/rabin_miller.h"
#include "prime/solovay_shtrassen.h"
#include "prime/agrawal.h"

std::ostream &operator<<(std::ostream &output, TInteger a) {
    return output << (std::string)a;
}

int main() {
    TInteger a(123), b("456");

    // Should output:
    // 12345
    // 54321

    // It means, that Karatsuba was the first method
    // and Modular the second

    Multiplication* method = new Karatsuba;
    std::cout << method->multiply(a, b) << "\n";

    method = new Modular;
    std::cout << method->multiply(a, b) << "\n";

    return 0;
}
