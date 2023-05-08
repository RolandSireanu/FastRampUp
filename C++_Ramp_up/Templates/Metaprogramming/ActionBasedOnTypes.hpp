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

// ================ Alternative implementation based on std::true_type , std::false_typoe
// In this way you no longer have to write a specialization for int&, const int, const int& etc
template<typename T>
struct is_int_value : public std::false_type
{};
template<>
struct is_int_value<int> : public std::true_type
{};

template<typename T>
struct is_int : public is_int_value<std::decay_t<T>>
{};

int main()
{
    if(is_int<float>::value)
        std::cout << "It's an int data type!" << std::endl;

    return 0;
}