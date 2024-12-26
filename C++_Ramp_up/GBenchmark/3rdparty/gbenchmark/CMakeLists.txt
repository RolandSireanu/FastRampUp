message(STATUS "Fetching gbenchmark ...")
FetchContent_MakeAvailable(googlebenchmark)

# Link Google Benchmark to the main target
# add_library(benchmark::benchmark ALIAS benchmark)
 