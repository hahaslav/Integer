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

int main(int argc, char *argv[]) {
    std::cout << argc << " values:";
    for (int i = 0; i < argc; i++) {
        std::cout << "\n" << argv[i];
    }

//    TInteger n(123), s("456");

//    std::cout << n.to_string() << ' ' << s.to_string();

    return 0;
}
