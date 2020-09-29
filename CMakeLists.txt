cmake_minimum_required(VERSION 3.17)
project(database C)

set(CMAKE_C_STANDARD 11)

add_executable(database main.c code/db.h code/db.c)