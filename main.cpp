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
     * [7; 10] - primality check methods
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
        case 0: {
            std::cout << a;
            if (second_integer_exist) {
                std::cout << ' ' << b;
            }
            break;
        }
        case 11: {
            if (! second_integer_exist) {
                std::cout << "Second integer is required. Aborting execution.";
            } else {
                std::cout << a + b;
            }
            break;
        }
        case 12: {
            if (! second_integer_exist) {
                std::cout << "Second integer is required. Aborting execution.";
            } else {
                std::cout << a - b;
            }
            break;
        }
        default:
            std::cout << "Not implemented!";
    }

    return 0;
}
