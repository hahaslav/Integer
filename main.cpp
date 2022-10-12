#include <iostream>
#include "TInteger.h"

#include "multiplication/karatsuba.h"
#include "multiplication/tom_cook.h"
#include "multiplication/modular.h"
#include "multiplication/schonhage_shtrassen.h"

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

    std::cout << a << '\n' << b << "\n" << a - b;

    return 0;
}
