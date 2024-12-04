#include <iostream>
#include <vector>
using namespace std;

// Doc link: https://pixelclear.github.io/technical/post/2019/02/08/Rvo-Nmrvo.html

class Widget
{
    public:
        Widget(int arg) : value(arg){ cout <<"Default constructor with param int\n"; }
        Widget() {cout << "Default constructor \n"; }
        Widget(const Widget& ) { cout<<"Copy constructor Widget \n"; }
        Widget(Widget&&) { cout<<"Move constructor Widget \n"; }

        Widget& operator=(const Widget&) { cout <<"Copy assigment operator \n"; }
        Widget& operator=(Widget&&) { cout<<"Move assigment operator\n"; }

        int value;
};

// Copy elision
// In case the argument is rvalue, compiler will built it dirrectly into "arg" memory
void f(Widget arg)
{
    return;
}

// There are two types of RVO (Return value optimizatoins)

// Unnamed RVO (Return value optimization)
// The temporary Widget instance is build dirrectly into "yourWidget" variable => Single constructor call
Widget buildWithRVO(int value)
{
    return Widget{value};
}

// NRVO (Named return value optimization)
// NRVO makes compiler to optimized even when we return objects that are created inside function and has name.
// Variable temp is build dirrectly into the memory of "myWidget" => Single constructor call
Widget buildWidget(int value)
{
    Widget temp{value};
    return temp;
}

// When the RVO is not applied
    // When the return type != type being returned
    // Multiple return statement with different objects
    // When it returns a complex expression (when there is not a lvalue or a prvalue)

// In which situations the compiler will most probably apply RVO?
    // -> Single return path
    // -> Same type for the ret value and the type of returned object
    // -> Simple logic, without many branches
/*
    Generally, if a function appears to have a simple and straightforward structure, 
    without complex branching, aliasing, or interactions that would make the lifetime of the returned object ambiguous, 
    compilers are more likely to detect and apply RVO.
    
    Compiler flag that highlights situations where compiler couldn't apply RVO -Wnrvo
*/


int main()
{
    // Copy elision, Widget instance will be build directly in the function argument variable
    // There will be a single call to constructor (Widget(int))
    f(Widget{5});
    Widget myWidget = buildWidget(5);
    Widget yourWidget = buildWithRVO(5);
    return 0;
}