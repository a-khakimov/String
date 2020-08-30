cmake_minimum_required(VERSION 3.5)


project(mystring VERSION 1.0.0 DESCRIPTION "Custom String container")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(mystring SHARED
    src/String.cpp
)


## Unit tests
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
