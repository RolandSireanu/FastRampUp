#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

class Widget
{

};

//Distinguish universal reference from rvalue reference
void f(Widget&&);               //Rvalue reference , type is specified
Widget&& var2 = Widget();       //Rvalue reference , type is specified
auto&& var = Widget();          //Universal reference , type is deduced

template<typename T>
void f(vector<T>&& arg);        //Rvalue reference , type is specified

//Universal references T&& can behave as an rvalue ref or as an lvalue reference
//Universal references differ from rvalue references through type deduction


//Here T&& is not a universal reference , because push_data can't exists without
//an instantiation of Buffer class , which can be instantiated with any type
//example bellow. 

template<typename T>
class Buffer
{
    public:
    void pushData(T&& arg)
    {}

    //Args&& is an universal reference
    //Implies type deduction
    template<typename... Args>
    void emplace_data(Args&&... args);
};

//Not T&& is int&& rvalue reference
template<>
class Buffer<int>
{
    public:
        void pushData(int&& arg)
        {}
};



//Variables declared with auto&& are always universal references because
//auto implies type deduction

int main()
{


    return 0;
}