#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <span>
using namespace std;


namespace NN
{

// Use STRUCT if there is no invariant
// Don't define a class/enum and declare a variable of its type in the same statement
class Shape
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
    Operation() noexcept = default;
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

    // When a destructor needs to be declared just to make it virtual, it can be defined as defaulted.
    // A destructor must not fail, declare it NOEXCEPT
    // Destructor should be public and virtual
    virtual ~Operation() noexcept = default;
private:
    
    // Don't make data members const or references. This makes the class not suitable for copy-assigment operator (operator=)
    // // Prefer in-class initialization instead of member initialization in constructor
    int mId = 0;
    Shape mShape {0,0};
    string mName {"no_name"};
};

// Make operator == noexcept
bool operator==(Operation const& a, Operation const& b) noexcept {}

class NeuralNetworkOperation : public Operation
{
    // Use inheriting constructors to import constructors into a derived class that does not need further explicit initialization
    using Operation::Operation;
}

// Make a function a member only if it needs direct access to the representation of a class
// A helper function doesn't need direct access to the representation of the class, yet it is seen
// as part of the interface. It should be placed in the same namespace as the class to make their relation
// obvious
bool isShapeBigEnough(Operation const& aOperation)
{
    if(aOperation.shape().w > 100)
    {
        return true;
    }

    return false;
}

}

int main()
{
 
}