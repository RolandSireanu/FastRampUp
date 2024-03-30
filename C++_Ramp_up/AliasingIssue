int a = 10;
float* fp = reinterpret_cast<float*>(&a); // Pointer of type float* pointing to int memory
int* ip = &a; // Pointer of type int* pointing to the same int memory

*fp = 5.0f; // Modifying the memory through fp

// The compiler may not realize that the modification through fp affects the value seen through ip.

// Modifying the "a" memory area thorugh a float pointer is undefined behavior


// How to bypass the strict aliasing rule problem?
// Use char* or void* as an intermediate type
#include <iostream>

int main() {
    int a = 10;

    // Step 1: Cast the address of 'a' to a char* (character pointer)
    char* charPtr = reinterpret_cast<char*>(&a);

    // Step 2: Cast the char* to a float* (the target type)
    float* floatPtr = reinterpret_cast<float*>(charPtr);

    // Modify the memory through floatPtr
    *floatPtr = 5.0f;

    // Reading back through int pointer to observe the change
    int* intPtr = &a; // Directly using &a to get the pointer

    std::cout << "Original int value (interpreted as float): " << *floatPtr << std::endl;
    std::cout << "Memory location as int: " << *intPtr << std::endl;

    return 0;
}
