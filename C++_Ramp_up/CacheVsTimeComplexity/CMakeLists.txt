cmake_minimum_required(VERSION 3.10)
project(CacheVsComplexity)

# Find SFML package
find_package(benchmark REQUIRED)

# Now you can link SFML to your target
add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} benchmark::benchmark_main)