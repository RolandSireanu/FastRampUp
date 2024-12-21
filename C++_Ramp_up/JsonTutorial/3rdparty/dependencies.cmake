# Include the FetchContent module
include(FetchContent)

# Declare the nlohmann_json dependency

# When using FetchContent to bring in a library like nlohmann_json, 
# you generally don't need to explicitly call find_package. 
# This is because FetchContent_MakeAvailable both fetches the source 
# code and sets up the build system to provide the necessary targets directly. 
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY git@github.com:nlohmann/json.git
    GIT_TAG v3.11.2 # Specify the version tag you want to use
)


# Make the content available
FetchContent_MakeAvailable(nlohmann_json)

# Declare the oneTBB dependency
FetchContent_Declare(
    tbb
    GIT_REPOSITORY git@github.com:uxlfoundation/oneTBB.git
    GIT_TAG v2022.0.0 # Specify the version tag you want to use; you can change this as needed
)

# Make the content available
FetchContent_MakeAvailable(tbb)