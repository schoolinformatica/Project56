cmake_minimum_required(VERSION 3.3)
project(processing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(dbcon ${SOURCE_FILES})
