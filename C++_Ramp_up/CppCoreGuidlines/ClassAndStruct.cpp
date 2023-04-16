#include <string>
#include <chrono>
// Use CLASS if the class has an invariant and use STRUCT if the data members
// can vary independently 
// An invariant is a logical condition for the members of an object that a constructor must establish for the public member functions to assume. 
// After the invariant is established (typically by a constructor)

// No invariant here, color and engineCapacity can vary independently
struct Car
{
    string color;
    int engineCapacity;
};

// Inariant = count >= 0
class Stack 
{
       int count;
       Stack () : count(0) {}
       void push (void *);
       void *pop ();
};

// ===============================================================================================================
// Make a function a member only if it needs direct access to the representation of a class

namespace Art
{
class Color
{
    // ... implementation
};

//combineColor has no need to access the members of Color class, it shouldn' be part of Color
Color combineColors(Color aColor1, Color aColor2)
{ // It returns the color resulting from the combination of the two
};

// ================================================================================================================
// A helper function doesn't need direct access to the representation of the class, yet it is seen
// as part of the interface. It should be placed in the same namespace as the class to make their relation
// obvious
namespace Chrono { // here we keep time-related services

    class Time { /* ... */ };
    class Date { /* ... */ };

    // helper functions:
    bool operator==(Date, Date);
    Date next_weekday(Date);
    // ...
}

// ==================================================================================================================
// Don't define a class/enum and declare a variable of its type in the same statement
// BAD : struct Data { string day; } dataVariable; 

//Use class rather than a struct if any of the data members are private