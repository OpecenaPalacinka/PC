cmake_minimum_required(VERSION 3.16)
project(pelikanj_zadani2 C)

set(CMAKE_C_STANDARD 90)

add_executable(generator fsmgen.c)

add_executable(fsm fsm.c)

add_executable(pokus pokus.c)