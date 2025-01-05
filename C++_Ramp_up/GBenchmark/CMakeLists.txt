cmake_minimum_required(VERSION 3.10)
project(GBenchmark)

# Set build type to Release
set(CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_STANDARD 20)

add_subdirectory(3rdparty)

# Add benchmark target
add_executable(dummy_benchmark src/dummy_benchmark.cpp)

target_link_libraries(dummy_benchmark benchmark::benchmark boost_container)

