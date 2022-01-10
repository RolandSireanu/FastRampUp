file(GLOB SRC_FILES
"*.cpp"
)

target_sources(${CMAKE_PROJECT_NAME} PUBLIC ${SRC_FILES})