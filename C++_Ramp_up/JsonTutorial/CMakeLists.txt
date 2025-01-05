cmake_minimum_required(VERSION 3.14)  # Ensure CMake version supports FetchContent

project(JsonProject)

# set(CMAKE_GENERATOR "Ninja")
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_BUILD_TYPE Release)

# Include the dependencies.cmake file
include(3rdparty/dependencies.cmake)


# Add further CMake configuration here, e.g., add an executable or library
add_executable(${CMAKE_PROJECT_NAME}_SEQ main.cpp)
target_compile_options(${CMAKE_PROJECT_NAME}_SEQ PRIVATE -Wno-error)
target_compile_definitions(${CMAKE_PROJECT_NAME}_SEQ PRIVATE SEQ)

add_executable(${CMAKE_PROJECT_NAME}_PAR_TBB main.cpp)
target_compile_options(${CMAKE_PROJECT_NAME}_PAR_TBB PRIVATE -Wno-error)
target_compile_definitions(${CMAKE_PROJECT_NAME}_PAR_TBB PRIVATE PAR_TBB)

add_executable(${CMAKE_PROJECT_NAME}_PAR_STD main.cpp)
target_compile_options(${CMAKE_PROJECT_NAME}_PAR_STD PRIVATE -Wno-error)
target_compile_definitions(${CMAKE_PROJECT_NAME}_PAR_STD PRIVATE PAR_STD)

add_executable(${CMAKE_PROJECT_NAME}_PAR_CUSTOM main.cpp)
target_compile_options(${CMAKE_PROJECT_NAME}_PAR_CUSTOM PRIVATE -Wno-error)
target_compile_definitions(${CMAKE_PROJECT_NAME}_PAR_CUSTOM PRIVATE PAR_CUSTOM)

# Link the nlohmann_json library with your executable
target_link_libraries(${CMAKE_PROJECT_NAME}_SEQ         PRIVATE nlohmann_json::nlohmann_json TBB::tbb)
target_link_libraries(${CMAKE_PROJECT_NAME}_PAR_TBB     PRIVATE nlohmann_json::nlohmann_json TBB::tbb)
target_link_libraries(${CMAKE_PROJECT_NAME}_PAR_STD     PRIVATE nlohmann_json::nlohmann_json TBB::tbb)
target_link_libraries(${CMAKE_PROJECT_NAME}_PAR_CUSTOM  PRIVATE nlohmann_json::nlohmann_json TBB::tbb)
