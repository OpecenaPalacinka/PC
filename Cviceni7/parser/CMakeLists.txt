# cmake_minimum_required(VERSION <specify CMake version here>)
project(parser C)

set(CMAKE_C_STANDARD 11)

include_directories(parser)

add_executable(parser
        parser/operators.c
        parser/operators.h
        parser/parser.c
        parser/stack.c
        parser/stack.h)
