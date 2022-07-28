#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

struct my_type{};

// From C++14 to C++17 in metaprogramming

template<typename T, typename=void>
struct is_comparable 
{
    static constexpr bool value = false; 
};

template<typename T>
struct is_comparable<T, decltype((declval<T>() != declval<T>()), void())>
{
    static constexpr bool value = true; 
};


int main()
{
    if(is_comparable<int>::value)
        cout << "Yes it is " << endl;
    else
        cout << "No it isn't " << endl;

    return 0;
}