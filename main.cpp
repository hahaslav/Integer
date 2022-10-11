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

int charstring_to_int(char s[]) {
    int result = 0;

    for (int i = 0; s[i] != 0; i++) {
        result *= 10;
        result += s[i] - '0'; // it is converted from the ASCII character code
    }

    return result;
}

int main(int argc, char *argv[]) {
    /*
     * If executed from a shell,
     * the program takes these arguments:
     * - a number of a method
     * - first integer
     * - second integer
     *
     * Numbers of the methods:
     * 0 - outputs the given integers
     * [1; 4] - multiplication methods
     * 5 - float method
     * 6 - division method
     * [7; 10] - prime check methods
     * 11 - sum
     * 12 - subtraction
     * 13 - multiplication "in column"
     */
    if (argc == 1) {
        std::cout << "No arguments were given. Aborting execution.";
        return 0;
    }
    if (argc == 2) {
        std::cout << "Method " << argv[1] << " was chosen, bun no integers were given. Aborting execution.";
    }

    TInteger a(argv[2]), b;
    bool second_integer_exist = argc > 3;
    if (second_integer_exist) {
        b = TInteger(argv[3]);
    }

    switch (charstring_to_int(argv[1])) {
        case 0:
            std::cout << a.to_string();
            if (second_integer_exist) {
                std::cout << ' ' << b.to_string();
            }
            break;
        default:
            std::cout << "Not implemented!";
    }

    return 0;
}
