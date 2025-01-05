Standard instalation cmd:
conan install . --output-folder=build --build=missing

Instalation cmd for conan debug mode as shared lib:
conan install . --output-folder=build --build=missing --settings=build_type=Debug --options=zlib/1.2.11:shared=True

Config cmd:
cmake .. -DCMAKE_TOOLCHAIN_FILE=./build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
