#include <iostream>
#include <type_traits>
using namespace std;

//Partial specialization is not allowed for function
//but we can use enable_if on the return type with the same result

template<typename T, int value>
enable_if_t<value == 1>
f()
{
    //Manual specialization for value == 1
}


template<typename T, int value>
enable_if_t<value == 2>
f()
{
    //Manual specialization for value == 2
}