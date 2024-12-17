#include "header.hpp"
#include <iostream>
// Varibles by default have external linkage
// You can declare them extern in other source files

// If variable is declared static inside namespace it is the same as if it was declared
// static inside the cpp file in the global scope.

// In C++ const implies static at file scope

bool make();

int main()
{
    std::cout << "Main.cpp   " << std::hex << &Utils::a << " " << &Utils::b 
              << " " << &Utils::c << " " << &Utils::d << std::endl;

    if(make())
        return Utils::c;
    else
        return Utils::d;
}