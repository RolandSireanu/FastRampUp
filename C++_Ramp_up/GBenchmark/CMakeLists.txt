cmake_minimum_required(VERSION 3.10)
project(GBenchmark)

# Include dependencies
include(${CMAKE_SOURCE_DIR}/3rdparty/dependencies.cmake)

find_package(benchmark REQUIRED)
# ...existing code...

# Add benchmark target
add_executable(dummy_benchmark src/dummy_benchmark.cpp)
target_link_libraries(dummy_benchmark benchmark::benchmark)

