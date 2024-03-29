// Do not rely on transitive inclusions. This allows people to remove no-longer-needed #include statements from their headers without breaking clients.
// Include headers in the following order: Related header, C system headers, C++ standard library headers, other libraries' headers, your project's headers.
#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <span>
using namespace std;

// All declarations can be given internal linkage by placing them in unnamed namespaces.
namespace
{

// Make a function a member only if it needs direct access to the representation of a class
// A helper function doesn't need direct access to the representation of the class, yet it is seen
// as part of the interface. It should be placed in the same namespace as the class to make their relation
// obvious
bool isShapeBigEnough(Operation const& aOperation)
{
    if(aOperation.shape.w > 100)
    {
        return true;
    }

    return false;
}

}


// Use namespaces: Namespaces subdivide the global scope into distinct, named scopes, and so are useful for preventing name collisions in the global scope.
namespace NN
{
    // Prefer enumeration over macros
    // Prefer enum class over plain enums, traditional enums convert to int too easily
    // Don’t use ALL_CAPS for enumerators
    // Avoid unnamed enumerations
    // Specify the underlying type of an enumeration only when necessary

    enum class OperationType
    {
        // Specify enumerator values only when necessary
        conv, maxPooling, relu
    };

// Use STRUCT if there is no invariant
// Don't define a class/enum and declare a variable of its type in the same statement
struct Shape
{
    int w;
    int h;
};

// Use CLASS if there is an invariant that need to be mainted by the constructor
// Use class rather than a struct if any of the data members are private 
// Prefer concrete types of hierarchies, YOU NEED A REASSON TO USE A HIERARCHY, Runtime overhead to perform memory indirection
class Operation
{
public:
    // If you can avoid defining the constructors/destructors, do it
    // You should have a default constructor, many std containers relay on it. Make it simple&noexcept
    // Don’t define a default constructor that only initializes data members; use in-class member initializers instead
    // Don't call virtual functions in the constructor
    // How to signal an error in constructor? Crash the program if it is an option, otherwise use a Factory or an Init() method
    Operation() noexcept = default;

    // Alwasy mark conversion constructors and operators as explicit to avoid implicit conversion
    explicit Operation(int){}    // Conversion constructor
    explicit operator int() {}   // Conversion operator


    // Define and initialize member variables in the order of member declaration
    Operation(Shape const& aShape, int aId, string const& aOpName) : mId{aId}, mShape{aShape}, mName{aOpName} {}

    // Use delegating constructors to represent common actions for all constructors of a class
    Operation(Shape const& aShape, int aId) : Operation(aShape, aId, "default_name") {}
    // Use EXPLICIT for single argument constructors to avoid any unwanted conversion.
    explicit Operation(Shape const& aShape): Operation(aShape, 0) {}

    // To avoid object slicing problem a polymorphic class should suppress public copy/move
    Operation(Operation const&) = delete;
    Operation& operator=(Operation const&) = delete;

    const Shape& shape() { return mShape; }
    // Overload only for operations that are roughly equivalent
    Shape shape(int offset) { return Shape{mShape.w + offset, mShape.h}; }

    // Make interfaces precise and strongly typed, BAD example area(int aWidth, int aHeight)
    int area(Shape const& aArg) { return aArg.h * aArg.w; }
    
    // Use non-member functions for symetric operators
    // Make operator == noexcept
    friend bool operator==(Operation const& a, Operation const& b) noexcept { }

    // Don't introduce implicit conversion, either through conversion operators or non-explicit constructors
    // operator int() { return mShape.w + mShape.h; }       BAD
    // explicit operator int() { ... }   GOOD

    //If you don't use the smart pointer capabilities of arg, just take a raw pointer instead
    //Make sure arg it is managed by a smart pointer
    //DON'T CALL NEW OR DELETE ANYWHRERE IN YOUR CODE
    void f(int* arg)
    {

    }

    // For output value, prefer using the return value over params
    // Return by value, or by reference, return a raw pointer only if it can be null
    // Input params before output params in declaration
    int paramPassing(int inParam, const int& inParam2, int& outParam);


    // When a destructor needs to be declared just to make it virtual, it can be defined as defaulted.
    // A destructor must not fail, declare it NOEXCEPT
    // Destructor should be public and virtual
    virtual ~Operation() noexcept = default;

    // Alwasy add override and final keywords

private:
    
    // Don't make data members const or references. This makes the class not suitable for copy-assigment operator (operator=)
    // // Prefer in-class initialization instead of member initialization in constructor
    int mId = 0;
    Shape mShape {0,0};
    string mName {"no_name"};
};

class NeuralNetworkOperation : public Operation
{
    // Use inheriting constructors to import constructors into a derived class that does not need further explicit initialization
    using Operation::Operation;
};


// Use "using" for customization points. This is done by including the general function in the lookup for the function
void Interchange(Operation& a, Operation& b)
{
    using std::swap;
    //If it exists, use the specific swap implementation for Operation, otherwise use the std::swap
    swap(a, b);
}

// Rvalue reference and when to use it?
//      - move constructor/assigment operator
//      - define && qualified methods, suitable only for rvalue *this
//      - use in conjuction with std::forward to achive perfect forwarding
//      - define pairs of overloads like (const Foo& and Foo&&)

// Friends should be defined in the same translation unit.
// A common case is the Builder pattern

}

int main()
{
    NN::Operation op1, op2;
    // op1 = op1 + op2;
}