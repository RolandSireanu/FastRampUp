cmake_minimum_required(VERSION 3.10)
project(Sharing)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)


find_package(Threads REQUIRED)
find_package(benchmark REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} src/dataPacking.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} Threads::Threads benchmark::benchmark)
