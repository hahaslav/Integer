cmake_minimum_required(VERSION 3.23)
project(integer)

set(CMAKE_CXX_STANDARD 14)

include_directories(TInteger)

add_executable(integer main.cpp multiplication/karatsuba.cpp multiplication/tom_cook.cpp multiplication/modular.cpp multiplication/schonhage_shtrassen.cpp cook/float_cook.cpp cook/float_cook.h cook/division_cook.cpp cook/division_cook.h prime/fermat.cpp prime/rabin_miller.cpp prime/solovay_shtrassen.cpp prime/agrawal.cpp TInteger/TInteger.cpp TInteger/TInteger.h multiplication/Multiplication.h prime/Prime.h)
