cmake_minimum_required(VERSION 3.3)
project(input_process)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES RunAllTests.cpp)
add_executable(input_UnitTests ${SOURCE_FILES})