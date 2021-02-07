#include <iostream>


//Member function generation
//Special member functions are the ones that c++ is willing to generated on its own
//C++98 : Default constructor ,destructor, copy constructor , copy assigment operator
//All these functions are generated only if they are used , but not declared.
//A default constructor is generated only if the class doesn't declare a constructor at all
//This prevents compilers from creating a default constructor for a class where you’ve specified that
//constructor arguments are required
//Implicitly generated functions are public and inline and non virtual unless
//the function in case , it is a destructor in a derived class with a base class virtual
//destructor

//With C++11 there are two more special functions : 
//  - Move assigment operator
//  - Move constructor
//The two move operations are not independent . By declaring one of them , you prevent
//the compiler in declaring the other one.
//The rationale is that if you declare, say, a move
// constructor for your class, you’re indicating that there’s something about how move
// construction should be implemented

//Copy operating are independent but move operation are not.

//If you declare one , declare them ALL !!!!!!


class Buffer
{
public:
    Buffer(){}
    ~Buffer(){}
    Buffer(const Buffer& b){}
    Buffer& operator=(const Buffer& b){}
    Buffer(Buffer&& b){}
    Buffer& operator=(Buffer&& b){}
};


int main()
{


    return 0;
}