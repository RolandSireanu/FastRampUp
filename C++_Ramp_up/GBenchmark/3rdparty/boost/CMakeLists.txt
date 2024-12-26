message(STATUS "Fetching boost ...")
FetchContent_MakeAvailable(boost)

# Link Google Benchmark to the main target
# add_library(benchmark::benchmark ALIAS benchmark)
 