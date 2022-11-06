# Very long integer class TInteger with various methods of multiplying methods, primality checking methods and other, in C++.

### TInteger class overloaded operators:

* Arithmetic: `+` `-` `*` `/` `%`
* Comparison: `==` `!=` `>` `>=` `<` `<=`
* Type conversion: `std::string` `int`
* Ostream/cout `<<`

### Implemented methods:

* [X] Karatsuba multiplication method
* [X] Tom-Cook multiplication method
* [ ] Modular multiplication method
* [ ] Schönhage-Strassen multiplication method
* [X] The Best Multiplication Method Ever 🤩 (WOW)
* [X] Newton's inverse method
* [ ] Cook division method?
* [X] Fermat primality check method
* [X] Rabin-Miller primality check method
* [X] Solovay-Strassen primality check method
* [X] Agrawal-Kayal-Saxena primality check method

## Building

To build an executable for 64-bit Windows, I used MinGW w64 9.0 and CMake 3.23.2. [More](CMakeLists.txt)

## Usage

The app takes arguments from a shell.

Usage: `integer.exe [number of a method] [first integer] {second integer}`

Numbers of the methods:
* `0` - Output the given integers
* `1` - Karatsuba multiplication method
* `2` - Tom-Cook multiplication method
* `5` - Newton's inverse method
* `7` - Fermat primality check method
* `8` - Rabin-Miller primality check method
* `9` - Solovay-Strassen primality check method
* `10` - Agrawal-Kayal-Saxena primality check method
* `11` - Sum
* `12` - Subtraction
* `13` - Multiplication "in column"
* `14` - Division
* `15` - Remainder from division
* `16` - The Best Multiplication Method Ever 🤩 (WOW)

## Testing

This repository also contains a [testing script](tests.py) in Python that runs all methods with random numbers, compares the results with python's fast and (*I hope*) correct results. To use this script, you need to install `sympy` (or remove the parts of the script that tests the primality check methods). After running the script, you can check a report in `test.txt`, where you can find out if the test was passed, its inputs and outputs and how much time it took to finish.