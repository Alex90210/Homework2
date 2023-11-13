cmake_minimum_required(VERSION 3.26)
project(Homework2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Homework2 main.cpp
        math_functions.cpp
        math_functions.h
        binary_operations.cpp
        random_generators.cpp
        random_generators.h
        genetic_algorithm.cpp
        genetic_algorithm.h
        genetic_operators.cpp
        genetic_operators.h)

