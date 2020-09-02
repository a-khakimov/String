cmake_minimum_required(VERSION 3.8)

project(String)
add_executable(example src/String.cpp src/example.cpp)
set_target_properties(example PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

## Unit tests
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
