cmake_minimum_required(VERSION 3.19)
project(quickSort_project C)

set(CMAKE_C_STANDARD 99)

add_library(methods
        ../include/methods.h)

add_executable(quickSort_project main.c ../include/methods.h)
