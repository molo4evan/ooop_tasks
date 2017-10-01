cmake_minimum_required(VERSION 3.8)
project(tritset)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp tritset.cpp tritset.h trit_pointer.cpp trit_pointer.h utilites.h utilites.cpp)
add_executable(tritset ${SOURCE_FILES})