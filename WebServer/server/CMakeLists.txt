file(GLOB SRC_FILES
"*.cpp"
)

target_compile_options(server_project PUBLIC -lpthread)
target_sources(server_project PUBLIC ${SRC_FILES})