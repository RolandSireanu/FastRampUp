#include <iostream>

// Allthough the object is of type DerivedClass the BaseClass::vMethod gets called.
// This is because the vMethod is non-virtual
// Method Dispatching: The method talk() in BaseClass calls vMethod(). However, the type of the method being called during this call is determined by the type of the pointer or reference, not by the actual object being used. 
// In this case, talk() is defined in BaseClass and calls the vMethod() defined in the same class.
class BaseClass
{
public:

    void talk() { vMethod(); }
    void vMethod() {std::cout << "BaseClass::vMethod" << std::endl;}

};

class DerivedClass : public BaseClass
{
public:
    void vMethod() { std::cout << "DerivedClass::vMethod" << std::endl; }
};

int main()
{
    DerivedClass d;
    d.talk();

    return 0;
}