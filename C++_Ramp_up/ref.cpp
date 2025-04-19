#include <cstdio>
#include <stdint.h>
#include <functional>

// The std::ref become usefull especially when you have a callback that takes a reference,
// like when you start a thread that takes a reference as argument.
void offload(int32_t& aValue)
{
    // work ....
}


// Ok but how std::ref works?
// std::ref -> produces a reference_wrapper<T> that keeps a pointer to given argument.
// It has the T& operator defined which return a reference to *ptr; 
// The operator T& get called in case of an implicit conversion to T&.
// An implicit conversion is triggered even when the reference_wrapper is used inside an expression, like ++

// Example:
// template<typename T>
// void add(T arg)
// {
//   arg++;
// }

// /* First instantiated from: insights.cpp:15 */
// #ifdef INSIGHTS_USE_TEMPLATE
// template<>
// void add<std::reference_wrapper<int> >(std::reference_wrapper<int> arg)
// {
//   arg.operator int &()++;
// }
// #endif


// int main()
// {
//   int var = 3;
//   add(std::ref(var));
//   return var;
// }


int main()
{
    int32_t lValue {4} ;
    auto callable = std::bind(offload, std::ref(lValue));
    callable();

    return 0;
}