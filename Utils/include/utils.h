#include <iostream>

template<typename T>
void print(T arg)
{
    std::cout << arg << std::endl;
}

template<typename Targ, typename... Targs>
void print(Targ arg, Targs... args)
{
    std::cout << arg << " ";
    print(args...);
}