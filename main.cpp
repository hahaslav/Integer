#include <iostream>
#include "TInteger.h"

#include "multiplication/karatsuba.h"
#include "multiplication/thoma_cook.h"
#include "multiplication/schonhage.h"
#include "multiplication/shtrassen.h"

#include "kuka/float_kuka.h"
#include "kuka/division_kuka.h"

#include "prime/ferma.h"
#include "prime/rabin_miller.h"
#include "prime/solovey_shtrassen.h"
#include "prime/ahravala.h"

std::ostream &operator<<(std::ostream &output, TInteger a) {
    return output << (std::string)a;
}

int main() {
    TInteger a(123), b("456");

    std::cout << a << '\n' << b << "\n" << a - b;

    return 0;
}
