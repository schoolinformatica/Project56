cmake_minimum_required(VERSION 3.3)
project(dbcon)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(dbcon ${SOURCE_FILES})