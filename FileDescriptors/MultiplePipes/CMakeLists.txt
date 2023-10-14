cmake_minimum_required(VERSION 3.13)
project(MultiplePipes)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../../Utils/cmake")

add_executable(${CMAKE_PROJECT_NAME})

add_subdirectory(./src)
#find_package(Utils)
