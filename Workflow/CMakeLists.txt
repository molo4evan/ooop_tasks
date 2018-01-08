cmake_minimum_required(VERSION 3.9)
project(Workflow)

set(CMAKE_CXX_STANDARD 11)

add_executable(Workflow main.cpp Workflow.cpp Workflow.h Executor.cpp Executor.h Parser.cpp Parser.h Worker.cpp Worker.h ArgParser.cpp ArgParser.h FlowExcept.cpp FlowExcept.h shared_ptr.cpp shared_ptr.h)