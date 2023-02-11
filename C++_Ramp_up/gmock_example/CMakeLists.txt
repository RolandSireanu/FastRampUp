

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(example test.cpp)
target_link_libraries(example gtest gtest_main gmock gmock_main)
add_test(NAME BasicAssertions COMMAND example)