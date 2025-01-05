cmake_minimum_required(VERSION 3.10)
project(SfmlGame)

# Find SFML package
find_package(SFML REQUIRED)

# Now you can link SFML to your target
add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} sfml::sfml)