cmake_minimum_required(VERSION 3.23)
project(integer)

set(CMAKE_CXX_STANDARD 14)

include_directories(TInteger)

add_executable(integer main.cpp multiplication/karatsuba.cpp multiplication/karatsuba.h multiplication/tom_cook.cpp multiplication/tom_cook.h multiplication/modular.cpp multiplication/modular.h multiplication/schonhage_shtrassen.cpp multiplication/schonhage_shtrassen.h cook/float_cook.cpp cook/float_cook.h cook/division_cook.cpp cook/division_cook.h prime/fermat.cpp prime/fermat.h prime/rabin_miller.cpp prime/rabin_miller.h prime/solovay_shtrassen.cpp prime/solovay_shtrassen.h prime/agrawal.cpp prime/agrawal.h TInteger/TInteger.cpp TInteger/TInteger.h multiplication/Multiplication.cpp multiplication/Multiplication.h prime/Prime.cpp prime/Prime.h)

set(CMAKE_EXE_LINKER_FLAGS "-static")
