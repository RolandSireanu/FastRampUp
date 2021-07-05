cmake_minimum_required(VERSION 3.14)
project(Particles)
# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)
set(COMPILE_OPTIONS "-Wall")
set(LIBS "-lsfml-graphics" "-lsfml-window" "-lsfml-system" "-lpthread")
add_executable(particle)

add_subdirectory(src)
target_compile_options(particle PRIVATE ${COMPILE_OPTIONS})
target_link_libraries(particle PRIVATE ${LIBS})
include("./include/add_include_path.cmake")

if(EnableTests)
    include(FetchContent)
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/355d57d90d9744c41ac7c99f1e960778f1c63040.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    add_definitions(-DEnableTests)

    enable_testing()

    target_sources(particle PRIVATE "./tests/basic_tests.cc")

    target_link_libraries(
        particle
        PRIVATE
        gtest_main
        )
    
    include(GoogleTest)
    gtest_discover_tests(particle)

endif()
