cmake_minimum_required(VERSION 3.8)
project(life_game)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp Game.cpp Game.h Field.cpp Field.h Cell.cpp Cell.h game_except/main_except.cpp game_except/main_except.h Executor.cpp)
add_executable(life_game ${SOURCE_FILES} Tests/test.cpp)
target_link_libraries(life_game gtest gtest_main)