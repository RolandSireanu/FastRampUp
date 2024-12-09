# 3rdparty/dependencies.cmake

# Set Boost version and the installation directory
set(Boost_VERSION "1.86.0")
set(Boost_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/boost_${Boost_VERSION}")
set(Boost_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/boost_install")
set(CMAKE_PREFIX_PATH ${Boost_INSTALL_DIR} ${CMAKE_PREFIX_PATH})

# Function to clone, build, and install Boost
function(configure_boost)
    # Check if Boost is already installed
    if(EXISTS "${Boost_INSTALL_DIR}/lib/cmake/Boost-*-*-*-*/BoostConfig.cmake")
        message(STATUS "Boost is already installed at ${Boost_INSTALL_DIR}.")
        return()
    endif()

    # Check if Boost source is already cloned
    if(EXISTS "${Boost_SOURCE_DIR}")
        message(STATUS "Boost is already cloned at ${Boost_SOURCE_DIR}.")
        
        # Check if Boost has been built
        if(EXISTS "${Boost_SOURCE_DIR}/build")
            message(STATUS "Boost build directory found. Building Boost...")
            # Build and install Boost
            execute_process(
                COMMAND cmake --build ${Boost_SOURCE_DIR}/build -j --target install
                WORKING_DIRECTORY ${Boost_SOURCE_DIR}/build
                RESULT_VARIABLE cmake_install_result
            )
            if(NOT cmake_install_result EQUAL 0)
                message(FATAL_ERROR "Boost installation failed.")
            endif()
            message(STATUS "Boost installed successfully at ${Boost_INSTALL_DIR}.")
            return()
        else()
            message(STATUS "Boost is cloned but not built. Building now...")
        endif()
    else()
        # Clone Boost repository
        message(STATUS "Cloning Boost from GitHub...")
        execute_process(
            COMMAND git clone --branch boost-${Boost_VERSION} --recursive https://github.com/boostorg/boost.git ${Boost_SOURCE_DIR}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            RESULT_VARIABLE git_clone_result
        )

        if(NOT git_clone_result EQUAL 0)
            message(FATAL_ERROR "Failed to clone Boost repository.")
        endif()

        # Creating build directory
        file(MAKE_DIRECTORY "${Boost_SOURCE_DIR}/build")
    endif()

    # Configure Boost with CMake
    message(STATUS "Configuring Boost...")
    execute_process(
        COMMAND cmake -S ${Boost_SOURCE_DIR} -B ${Boost_SOURCE_DIR}/build -DCMAKE_INSTALL_PREFIX=${Boost_INSTALL_DIR}
        WORKING_DIRECTORY ${Boost_SOURCE_DIR}/build
        RESULT_VARIABLE cmake_configure_result
    )
    
    if(NOT cmake_configure_result EQUAL 0)
        message(FATAL_ERROR "Boost configuration failed.")
    endif()

    # Build and install Boost
    message(STATUS "Building and installing Boost...")
    execute_process(
        COMMAND cmake --build ${Boost_SOURCE_DIR}/build -j --target install
        WORKING_DIRECTORY ${Boost_SOURCE_DIR}/build
        RESULT_VARIABLE cmake_build_result
    )

    if(NOT cmake_build_result EQUAL 0)
        message(FATAL_ERROR "Boost installation failed.")
    endif()

    message(STATUS "Boost installed successfully at ${Boost_INSTALL_DIR}.")
endfunction()

# Call the function to configure Boost
configure_boost()