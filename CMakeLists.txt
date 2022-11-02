cmake_minimum_required(VERSION 3.23)
project(integer)

set(CMAKE_CXX_STANDARD 14)

include_directories(TInteger)

add_executable(integer main.cpp multiplication/karatsuba.cpp multiplication/tom_cook.cpp multiplication/modular.cpp multiplication/schonhage_strassen.cpp PseudoFloat/inverse.cpp PseudoFloat/division_cook.cpp prime/fermat.cpp prime/rabin_miller.cpp prime/solovay_strassen.cpp prime/agrawal.cpp TInteger/TInteger.cpp TInteger/TInteger.h multiplication/Multiplication.h prime/Prime.h multiplication/repeated_addition.cpp PseudoFloat/PseudoFloat.h)

set(CMAKE_EXE_LINKER_FLAGS "-static")