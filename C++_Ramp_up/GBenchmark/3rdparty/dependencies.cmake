include(ExternalProject)

# # Add Google Benchmark as an external project
# ExternalProject_Add(
#   google_benchmark
#   GIT_REPOSITORY https://github.com/google/benchmark.git
#   GIT_TAG v1.8.0
#   CMAKE_ARGS -DBENCHMARK_ENABLE_TESTING=OFF -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON
#   PREFIX ${CMAKE_BINARY_DIR}/google_benchmark
#   INSTALL_COMMAND ""
# )

# # Add Boost as an external project
# ExternalProject_Add(
#   boost
#   GIT_REPOSITORY https://github.com/boostorg/boost.git
#   GIT_TAG boost-1.76.0
#   PREFIX ${CMAKE_BINARY_DIR}/boost
#   INSTALL_COMMAND ""
# )

set(GBENCHMARK_INSTALL_DIR ${CMAKE_BINARY_DIR}/google_benchmark_install)

# Define the target for Google Benchmark
ExternalProject_Add(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.9.1 # You can specify a specific tag or commit
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${GBENCHMARK_INSTALL_DIR} -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON
)

# Set the benchmark_DIR to the installation path
set(benchmark_DIR ${GBENCHMARK_INSTALL_DIR}/cmake/benchmark)

# Try to find the Google Benchmark package
# find_package(benchmark REQUIRED CONFIG PATHS ${benchmark_DIR})