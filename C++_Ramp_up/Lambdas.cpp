#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <string>
using namespace std;

//Lambda expressions 
//Are threated by compiler as functors .
//For every lambda expre a class with operator () overloaded is created

//Closure class = class from which a closure is instantiated

//Closure = runtime object created by lambda , where captured data is stored
//depending on capture mode.

//Capture modes 
// [&] capture all scope by reference
// [=] capture all scope by value

// Long-term, it’s simply better software engineering to explicitly list the local variables
// and parameters that a lambda depends on.
//In this way you can avoid dangling references
using Filters = vector<function<bool(unsigned int)>>;

Filters flt;
void addToFlt()
{
    unsigned int x = 15;

    //Capture everything by ref.
    //Reference to x will dangle after function addToFlt finish
    //It is better to specify which variables are you capturing by ref [&x]
    flt.emplace_back([&](int arg){
        return arg > x;
    });

}

// • Default by-reference capture can lead to dangling references.
// • Default by-value capture is susceptible to dangling pointers (especially this),
// and it misleadingly suggests that lambdas are self-contained.


//Moving objects into closure 
//In C++11 is not possible to move in closure , just copy or reference
//In c++14 , for moving objects (like move only data types unique_ptr , 
//or containers fast to move) we have "init capture"

class Buffer
{};

unique_ptr<Buffer> uptr(new Buffer());
auto closureA = [clsBuffer = move(uptr)](){

};


//From c++14 we can have type deduction in lambda's arguments 
void normalize(Buffer&& arg)
{

}

auto f = [](auto&& arg){
    return Buffer(forward<decltype(arg)>(arg));
};


int main()
{

    unsigned int x = 0;

    auto closure1 = [x](int y) 
    { 
        unsigned int temp = x*y;
        return temp;
    };

    auto closure2 = closure1;   //closure2 is a copy of closure1


    return 0;
}