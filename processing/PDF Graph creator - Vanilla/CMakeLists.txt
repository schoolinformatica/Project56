cmake_minimum_required(VERSION 3.3)
project(pdf)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    pdf/example.cpp
    pdf/metrics.cpp
    pdf/metrics.h
    pdf/pdf.cpp
    pdf/pdf.h)

add_executable(pdf ${SOURCE_FILES})