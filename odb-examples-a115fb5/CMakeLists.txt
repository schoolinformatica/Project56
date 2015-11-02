cmake_minimum_required(VERSION 3.3)
project(odb_examples_a115fb5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    database.hxx
    driver.cxx
    person-odb.cxx
    person-odb.hxx
    person.hxx)

add_executable(odb_examples_a115fb5 ${SOURCE_FILES})