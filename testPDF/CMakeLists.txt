cmake_minimum_required(VERSION 3.3)
project(testPDF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CURLCPP_INCLUDE_DIRS "@CURLCPP_SOURCE_DIR@/include")
set(CURLCPP_LIBRARY_DIRS "@CURLCPP_BINARY_DIR@/src")
set(CURLCPP_LIBRARIES "@CURLCPP_LIB_LOCATION@")
set(SOURCE_FILES main.cpp)
add_executable(testPDF ${SOURCE_FILES})



