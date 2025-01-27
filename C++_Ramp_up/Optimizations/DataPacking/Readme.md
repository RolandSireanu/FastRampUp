Build instructions:
    conan install . --output-folder=build --build=missing --settings=build_type=Release
    cmake .. -DCMAKE_TOOLCHAIN_FILE=./build/Release/generators/conan_toolchain.cmake
    cmake --build . -j

A more detailed description of the problem can be found here:
    https://medium.com/@sireanu.roland/false-sharing-problem-56d9f4507a5d