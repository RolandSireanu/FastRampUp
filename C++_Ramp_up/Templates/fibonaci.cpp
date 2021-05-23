#include <iostream>
#include <array>
using namespace std;
template<int limit>
struct Fib
{
    static constexpr int value = Fib<limit-1>::value + Fib<limit-2>::value;
};

template<>
struct Fib<1>
{
    static constexpr int value = 1;
};

template<>
struct Fib<0>
{
    static constexpr int value = 0;
};


int main()
{
    cout << Fib<6>::value << endl;

    return 0;
}