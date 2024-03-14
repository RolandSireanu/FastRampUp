#include <iostream>
#include <vector>
using namespace std;

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


class TestClass
{
public:
    void f() & { cout << " & " << endl;}                // Choosen for lvalue
    void f() && { cout << " && " << endl; }             // Choosen for rvalue
    void f() const& { cout << " const& " << endl;}      // Choosen for const lvalue
    void f() const&& { cout << " const&& " << endl; }   // Choosen for const rvalue
};

