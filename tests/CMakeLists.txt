cmake_minimum_required(VERSION 3.8)
message(STATUS "Starting to configure String Tests..")
enable_testing()

set(TEST_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../src/String.cpp)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(boost_tests_run tests.cpp)
set_target_properties(boost_tests_run PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
target_link_libraries(boost_tests_run ${Boost_LIBRARIES} ${TEST_SOURCE})
include_directories(${Boost_INCLUDE_DIRS})
