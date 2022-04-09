#include <cstdlib>
#include <iostream>
#include <string> 
#include <vector>
#include <memory>
#include <string.h>
using namespace std;


//Copy elision is a techinique used by the compiler to eliminate
//temp objects. Not part of C++ standard but most compiler implements
// it automatically.

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

//===== Return by value without copy elision 
Widget build_widget()
{
    // 1. Create a Widget object => Widget()
    Widget arg;
    // 2. Ret by value so a copy of arg is done, => Widget(&&)
    return arg;
}

int f()
{
    return 5;
}

int main()
{
    // 3. build_widget returns a temp object => Widget(&&) to 
    // create the final w1 variable
    // Without copy elision we had a call to Default constructor
    // and two calls to move constructor
    Widget w1 = build_widget();
    cout << w1.value << endl;
    // If copy elision would be running a single call to 
    // default constructor would take place. 
    // The arg local variable would be constructed in w1 mem location

    //Compiler will expand this to : Widget w2 = Widget(5)
    // by copy elision optimization the temporary object will be 
    // elided => Move constructor will not be called, just the Default
    // constructor with params and w2 as "this"
    Widget w2 = 5;  
    cout << f();


}
