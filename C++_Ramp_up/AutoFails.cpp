#include <iostream>
#include <vector>

// • “Invisible” proxy types can cause auto to deduce the “wrong” type for an ini‐
//   tializing expression.
// • The explicitly typed initializer idiom forces auto to deduce the type you want
//   it to have.


double f()
{
    return 1.0;
}

int main()
{
    std::vector<bool> v{true,false,true};

    bool e = v[0];  //::reference is converted to bool and e is bool

    auto a = v[0];      //a will be std::vector<bool>::reference not just bool
                        //C++ forbids reference to bids

    // vector<>::reference is a "invisibly" proxy class , it emulates the reference
    // to a bool . 

    //Using the typed initializer idiom is the right way here
    auto correct = static_cast<bool>(v[0]);

    //Explicitly downsize the type from double to float
    float r = static_cast<float>(f());


    return 0;
}