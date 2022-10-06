#include <iostream>
#include <span>
#include <vector>
#include <vector>
using namespace std;

//Make distinction between multiple data types
template<typename T, T v>
struct integral
{ 
    enum{value = v};
};
using true_t = integral<bool, true>;
using false_t = integral<bool, false>;

template<typename T>
struct is_int {};

template<>
struct is_int<int> : true_t {};

template<>
struct is_int<unsigned char> : true_t {};

template<>
struct is_int<float> : false_t {};


int main()
{
    if(is_int<float>::value)
        std::cout << "It's an int data type!" << std::endl;

    return 0;
}