#include <iostream>
using namespace std;

// =============== Ref qualified functions ==============
// During overload resolution the compiler looks for the function &-qualified 
// if the caller object is an lvalue or for the function &&-qualified if the caller object is an rvalue.
// &:       The & qualifier after a member function declaration in C++ is called an "lvalue reference qualifier". This qualifier indicates that the function can only be called on lvalue expressions of the class
// const&:  const:  This qualifier indicates that the member function does not modify any non-static member variables of the class. It can be called on both const and non-const instances of the class
//          &:      Called only on lvalue objects
//          const&: Doesn't modify the object and can be called only on lvalue expressions  
// &&:      Rvalue reference qualifier, the function can only be called on rvalue expressions

class Container
{
public:

    void begin() const& { std::cout << "const&" << std::endl;}
    // void begin(const int*&)
    // Can bind lvalue const/non-const "this" pointer: constantContainer.begin()
    // Can bind rvalue "this" pointer: Container{}.begin()
    
    void begin() & {std::cout << "-" << std::endl; }
    //  void begin(Container*&)
    //  Can bind lvalue "this" pointers: myContainer.begin()

    void begin() && {std::cout << "&&" << std::endl; }  
    //  void begin(Container*&&)
    //  Can bind only rvalue "this" pointers: Container{}.begin();

    // void begin() const {}
    // void begin(const Container*)
    // Can bind const and non-const lvalue "this" pointer: constantContainer.begin()
};


void f(int*& arg)       {}
void f(const int*& arg) {}
void f(int*&& arg)      {}

int main()
{

    Container c;
    Container const cc;
    Container{}.begin();

    c.begin();
    cc.begin();

    int a {1};
    const int* ptr = &a;
    int& ra = a;
    const int& cra = a;
    f(ptr);
    f(new int);
    return 0;
}
