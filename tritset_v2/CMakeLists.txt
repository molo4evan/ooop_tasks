cmake_minimum_required(VERSION 3.8)
project(tritset_v2)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp Tritset.cpp Tritset.h utilites.h Trit.cpp Trit.h utilites.cpp Reference.cpp InputIterator.cpp Tests/test.cpp)
add_executable(tritset_v2 ${SOURCE_FILES} Tests/test.cpp)
target_link_libraries(tritset_v2 gtest gtest_main)