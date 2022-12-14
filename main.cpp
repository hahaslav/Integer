#include <iostream>

#include "multiplication/Multiplication.h"
#include "PseudoFloat/PseudoFloat.h"
#include "prime/Prime.h"

std::ostream &operator<<(std::ostream &output, const TInteger &a) {
    return output << (std::string)a;
}

int charstring_to_int(char s[]) {
    int result = 0, i = 0;
    bool to_invert = false;
    if (s[0] == '-') {
        to_invert = true;
        i = 1;
    }

    for (i; s[i] != 0; i++) {
        result *= 10;
        result += s[i] - '0'; // it is converted from the ASCII character code
    }

    if (to_invert) {
        result *= -1;
    }
    return result;
}

int main(int argc, char *argv[])
// Check info about executing in README.md
{
    if (argc == 1) {
        std::cout << "No arguments were given. Aborting execution.";
        return 0;
    }
    if (argc == 2) {
        std::cout << "Method " << argv[1] << " was chosen, bun no integers were given. Aborting execution.";
        return 0;
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
        case 1: {
            if (! second_integer_exist) {
                std::cout << "Second integer is required. Aborting execution.";
            } else {
                Multiplication* multiply_method = new Karatsuba;
                std::cout << multiply_method->multiply(a, b);
            }
            break;
        }
        case 2: {
            if (! second_integer_exist) {
                std::cout << "Second integer is required. Aborting execution.";
            } else {
                Multiplication* multiply_method = new TomCook;
                std::cout << multiply_method->multiply(a, b);
            }
            break;
        }
        case 5: {
            std::cout << inverse(a);
            break;
        }
        case 7: {
            PrimalityCheck* is_prime = new Fermat;
            std::cout << is_prime->check(a);
            break;
        }
        case 8: {
            PrimalityCheck* is_prime = new RabinMiller;
            std::cout << is_prime->check(a);
            break;
        }
        case 9: {
            PrimalityCheck* is_prime = new SolovayStrassen;
            std::cout << is_prime->check(a);
            break;
        }
        case 10: {
            PrimalityCheck* is_prime = new Agrawal;
            std::cout << is_prime->check(a);
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
        case 13: {
            if (! second_integer_exist) {
                std::cout << "Second integer is required. Aborting execution.";
            } else {
                std::cout << a * b;
            }
            break;
        }
        case 14: {
            if (! second_integer_exist) {
                std::cout << "Second integer is required. Aborting execution.";
            } else {
                std::cout << a / b;
            }
            break;
        }
        case 15: {
            if (! second_integer_exist) {
                std::cout << "Second integer is required. Aborting execution.";
            } else {
                std::cout << a % b;
            }
            break;
        }
        case 16: {
            if (! second_integer_exist) {
                std::cout << "Second integer is required. Aborting execution.";
            } else {
                Multiplication* multiply_method = new RepeatedAddition;
                std::cout << multiply_method->multiply(a, b);
            }
            break;
        }
        default:
            std::cout << "Not implemented!";
    }

    return 0;
}