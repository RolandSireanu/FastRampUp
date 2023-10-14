cmake_minimum_required(VERSION 3.0.1)
project (WebServer)

# set(EXECUTABLE_OUTPUT_PATH "..")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
add_executable(client_project)
add_executable(server_project)

target_compile_options(client_project PUBLIC --std=c++11)
target_compile_options(server_project PUBLIC --std=c++11)

add_subdirectory(client)
add_subdirectory(server)

find_library(PTHREADS_LIB NAMES pthread)
if(NOT PTHREADS_LIB)
    message(FATAL_ERROR "Pthreads library not found !")
endif()

message(${PTHREADS_LIB})

target_link_libraries(client_project PUBLIC ${PTHREADS_LIB})
target_link_libraries(server_project PUBLIC ${PTHREADS_LIB})


