#include <iostream>
#include <vector>

// The power of free functions
// In a nutshell, your first option should be free functions

// High level values of software development
//  - Encapsulation
//  - Abstraction/Polymorphism/reuse/generality
//  - Extensiblity
//  - Testability
//  - Peformance

class Container
{
public:

private:
    std::vector<int> mVec {1,2,3,4,5};
};

// Instead of having it as a member function, we can make it a free function
// In this way is :
//      - encapsulated
//      - can be reused
//      - easily extenable
//      - more testable than a private method


//It respects 4 out of 5 design rules:
// - SRP
// - OCP (it is sealed, can be overloaded but not modified)
// - DRY (and reuse)

template<typename T>
void reset(std::vector<T>& aVec)
{
    for(auto& e : aVec)
    {
        e = 0;
    }
}

void reset(int& aInt)
{
    aInt = 0;
}


// Examples of free functions in std:
//  1. begin()
//  2. copy()
//  3. real()
//  4. etc


int main()
{

    return 0;
}