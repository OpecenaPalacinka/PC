cmake_minimum_required(VERSION 3.16)
project(Cviceni10)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(build)
include_directories(data)
include_directories(src)

add_executable(Cviceni10
        data/integers.txt
        data/persons.csv
        src/loader.c
        src/person.c
        src/person.h
        src/vector.c
        src/vector.h)
