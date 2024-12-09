cmake_minimum_required(VERSION 3.15)
project(MyProject)

include(ExternalProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set a variable for the Boost installation directory
set(BOOST_INSTALL_DIR ${CMAKE_BINARY_DIR}/installed/boost CACHE PATH "Installation directory for Boost")

# Include the dependencies script
include(${CMAKE_SOURCE_DIR}/3rdparty/dependencies.cmake)

add_subdirectory(Example1)