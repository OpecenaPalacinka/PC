cmake_minimum_required(VERSION 3.5)

project(spirals LANGUAGES C)
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -ansi")

add_executable(search_experiment
    search_experiment.c
    searchers/searchers.c
)

target_link_libraries(search_experiment m)
