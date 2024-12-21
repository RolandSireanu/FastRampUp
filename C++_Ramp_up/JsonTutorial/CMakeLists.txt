cmake_minimum_required(VERSION 3.14)  # Ensure CMake version supports FetchContent

project(JsonProject)

set(CMAKE_GENERATOR "Unix Makefiles")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the dependencies.cmake file
include(3rdparty/dependencies.cmake)


# Add further CMake configuration here, e.g., add an executable or library
add_executable(${CMAKE_PROJECT_NAME} main.cpp)

# Link the nlohmann_json library with your executable
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json TBB::tbb)
