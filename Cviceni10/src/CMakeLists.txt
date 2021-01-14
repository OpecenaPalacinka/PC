cmake_minimum_required(VERSION 3.5)

project(loader LANGUAGES C)
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -ansi -g")

add_executable(loader
    loader.c
    vector.c
    person.c
)
