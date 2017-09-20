cmake_minimum_required(VERSION 3.8)
project(task0b)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp sort_strings.cpp sort_strings.h)
add_executable(task0b ${SOURCE_FILES})