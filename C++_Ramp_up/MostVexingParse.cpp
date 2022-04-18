#include <iostream>
using namespace std;
class B {};
class A
{
    public:
        A(const B& arg) {}
};

int main()
{
    //You are not creating an instace of A class here ! 
    // This is the Most vexing parse problem
    //When the compiler sees Foo x(Bar()), it thinks that the Bar() part is declaring a non-member function that returns a Bar object, 
    // so it thinks you are declaring the existence of a function called x that returns a Foo 
    // and that takes as a single parameter of type “non-member function that takes nothing and returns a Bar.”
    A instance(B());

    //Correct syntax
    A instance_2{B()};
}