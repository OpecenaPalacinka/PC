# cmake_minimum_required(VERSION <specify CMake version here>)
project(sudoku C)

set(CMAKE_C_STANDARD 90)

add_executable(sudoku sudos.c sudoku.c)