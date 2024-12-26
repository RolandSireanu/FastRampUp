include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.9.1
)

set(BOOST_INCLUDE_LIBRARIES container)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(
  boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.85.0
)

add_subdirectory(gbenchmark)
add_subdirectory(boost)