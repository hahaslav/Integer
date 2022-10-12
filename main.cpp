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

int main() {
    TInteger a(123), b("456");

    std::cout << (std::string)a << '\n' << (std::string)b << "\n" << (std::string)(a - b);

    return 0;
}
