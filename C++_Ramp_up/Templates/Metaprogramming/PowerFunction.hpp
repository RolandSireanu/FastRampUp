#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

// From C++14 to C++17 in metaprogramming

template<size_t NR, size_t POW>
struct power
{
    static constexpr size_t value = NR * power<NR,POW-1>::value;
};


template<size_t NR>
struct power<NR,0>
{
    static constexpr size_t value = NR * 1;
};

//====================================================================
template<size_t NR, size_t POW>
size_t advanced_power()
{
    if constexpr(POW == 0)
        return NR * 1;
    else
        return NR * advanced_power<NR,POW-1>();
}



int main()
{
    cout << power<2,16>::value << endl;
    cout << advanced_power<2,16>() << endl;
    return 0;
}