cmake_minimum_required(VERSION 3.10)
project(MyTests)

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES main_test.cpp)

add_executable(runTests ${SOURCE_FILES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

add_test(NAME MyTests COMMAND runTests)