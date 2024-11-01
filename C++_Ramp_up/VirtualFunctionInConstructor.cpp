#include <iostream>

// Calling a virtual function inside the constructor can be missleading in terms
// of which method gets called. 
// In the current example, at construction and destruction the BaseClass::talk method
// gets called, although the object is of type DerivedClass. 
// During the execution of the BaseClass constructor, the talk() method is called. 
// Here is the critical point: when a virtual function is called from a base class constructor, the dynamic type of the object is not yet the derived class type. 
// Instead, it remains the base class type.

// The same principle applies to destructors. When the BaseClass destructor is invoked, if you call talk(), it will also call BaseClass::talk(), because at that point, the DerivedClass portion of the object is already destructed, and the BaseClass is what remains of the object.
// This means that even though talk() is a virtual function, the base class's implementation is executed because the object construction has not completed; the DerivedClass part of the object is not fully initialized yet.


class BaseClass
{
public:
    BaseClass() { talk(); }
    virtual void talk() { std::cout << "BaseClass::talk()" << std::endl; }
    virtual ~BaseClass() { talk(); }
};

class DerivedClass : public BaseClass
{
public:
    void talk() override {}
};

int main()
{
    DerivedClass d;

    return 0;
}