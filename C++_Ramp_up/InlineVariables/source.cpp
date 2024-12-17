#include "header.hpp"
#include <iostream>
#include <random>


bool make()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,10);

    std::cout << "Source.cpp " << std::hex << &Utils::a << " " << &Utils::b 
              << " " << &Utils::c << " " << &Utils::d << std::endl;

    if(Utils::a > dist6(rng) || Utils::b > dist6(rng) || Utils::c > dist6(rng) || Utils::d > dist6(rng))
        return true;
    else
        return false;
    
}