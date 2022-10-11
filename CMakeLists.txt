cmake_minimum_required(VERSION 3.23)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

include_directories(TInteger)

add_executable(lab2 main.cpp main.h multiplication/karatsuba.cpp multiplication/karatsuba.h multiplication/thoma_cook.cpp multiplication/thoma_cook.h multiplication/schonhage.cpp multiplication/schonhage.h multiplication/shtrassen.cpp multiplication/shtrassen.h kuka/float_kuka.cpp kuka/float_kuka.h kuka/division_kuka.cpp kuka/division_kuka.h prime/ferma.cpp prime/ferma.h prime/rabin_miller.cpp prime/rabin_miller.h prime/solovey_shtrassen.cpp prime/solovey_shtrassen.h prime/ahravala.cpp prime/ahravala.h TInteger/TInteger.cpp TInteger/TInteger.h multiplication/Multiplication.cpp multiplication/Multiplication.h prime/Prime.cpp prime/Prime.h)
