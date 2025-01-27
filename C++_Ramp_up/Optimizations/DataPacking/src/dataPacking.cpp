#include <benchmark/benchmark.h>
#include <vector>
#include <array>
#include <thread>
#include <numeric>
#include <iostream>

class Data
{
    bool b;
    int32_t i1;
    double d1;
    char c;
};




int main()
{
    std::cout << "sizeof(Data) = " << sizeof(Data) << "\n";
    return 0;
}