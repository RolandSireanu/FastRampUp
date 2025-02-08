cmake_minimum_required(VERSION 3.10)
project(Example1)

file(GLOB SOURCES "src/AsyncInMemoryDB.cpp")

find_package(Boost 1.86.0 COMPONENTS container asio REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES})