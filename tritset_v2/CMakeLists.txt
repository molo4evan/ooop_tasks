cmake_minimum_required(VERSION 3.8)
project(tritset_v2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Tritset.cpp Tritset.h utilites.h Trit.cpp Trit.h utilites.cpp Reference.cpp)
add_executable(tritset_v2 ${SOURCE_FILES})