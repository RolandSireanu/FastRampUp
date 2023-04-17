// =========================================================================
// If you can avoid defining the constructors/destructors, do it

// =========================================================================
// If you define or =delete any copy, move, or destructor function, define or =delete them all
// When a destructor needs to be declared just to make it virtual, it can be defined as defaulted.
    class Laptop
    {
    public:
        virtual void start() = 0;
        virtual ~Laptop() noexcept = default; 
    };


// ===========================================================================
// If a class inherits publically from a base class. The base class destructors
// should be either public and virtual, or protected and non-virtual

// A destructor must not fail, declare it NOEXCEPT

// ===========================================================================
// Implement a default constructor. Many std containers like vector relies on default initialization
#include <vector>
class ClassWithDefaultConstructor
{
public:
    ClassWithDefaultConstructor() : id{ 3 } noexcept { //simple and non-throwing }
    // BAD: Don’t define a default constructor that only initializes data members; use in-class member initializers instead
    //      ClassWithDefaultConstructor() noexcept : id{ 3 }, name { "John Doe " }  { /*simple and non-throwing*/ }
    

private:
    int id;
    string name;
};
vector<ClassWithDefaultConstructor> v(10);

// Use EXPLICIT for single argument constructors to avoid any unwanted conversion.
// Define and initialize member variables in the order of member declaration

// ===========================================================================
// Prefer in-class initialization instead of member initialization in constructor
// GOOD, constatn initializer use in-class initialization and mId uses member initialization 
// GOOD
class Car
{
public:
    Car(int aId) : mId { aId } {}

    int mId;
    string mName {"Dacia"};
    double mLength {235.98};
};


// ===========================================================================
// Use factory function if you need virtual behavior during initialization
// Don't call virtual function during initialization
class BaseLaptop
{
public:
    BaseLaptop()
    {
        // post_init() Don't call virtual function in constructors and destructors
    }
    virtual void post_init() = 0;
};

// Use delegating constructors to represent common actions for all constructors of a class
class Date
{
public:
    Date(int d, int m, int y) {}
    Date(int d, int m) : Date(d,m,2023) {}
}

// Use inheriting constructors to import constructors into a derived class that does not need further explicit initialization
class OddDate : public Date
{
    using Date::Date;
};