#include <iostream>
using namespace std;

template<typename T1, typename T2>
class MyType
{};

template<typename T1>
class MyType<T1,T1>
{
    //Partial specialization for T1 == T2
};