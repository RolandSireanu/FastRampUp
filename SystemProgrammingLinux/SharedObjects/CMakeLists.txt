PROJECT(sharedObject)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

SET(mylibSRCS sharedObject.cpp)
ADD_LIBRARY(mylib SHARED ${mylibSRCS})

add_executable(main main.cpp)