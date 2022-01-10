# file(GLOB SRC_FILES
# ${CMAKE_CURRENT_LIST_DIR}"/../src/*.cpp"
# )
# message(${${CMAKE_CURRENT_LIST_DIR})

# set(SRC_FILES "${CMAKE_CURRENT_LIST_DIR}/../src/utils.cpp")
# message(${SRC_FILES})
# target_sources(${CMAKE_PROJECT_NAME} PUBLIC ${SRC_FILES})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../include)