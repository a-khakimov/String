message(STATUS "")
message(STATUS "Starting to configure String Tests..")
message(STATUS "")
enable_testing()

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(TEST_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../src/String.cpp)

set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(boost_tests_run tests.cpp)
target_link_libraries(boost_tests_run ${Boost_LIBRARIES} ${TEST_SOURCE})

include_directories(${CMAKE_SOURCE_DIR}/src)
