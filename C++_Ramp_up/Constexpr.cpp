#include <iostream>
#include <utility>
#include <array>
//Constexpre indicates that a value that's not only constant , it's known
//during compilation time


//If values you pass to sum are known during compilation time
//the value will be computed during compilation
//When the arguments are not known at compile time , this function
//will act like a regular one , executing at runtime
//All function calls inside , should be constexpre too
constexpr int sum(int a , int b)
{
    unsigned int sum = 0;

    for(unsigned int i=0; i<(a+b); i++)
    {
        sum += i;
    }

    //std::cout << sum; Error , not a constexpr

    return sum;
}


// Recall that the constexpr in front of pow doesn’t say that pow returns a const value,
// it says that if base and exp are compile-time constants, pow’s result may be used as a
// compile-time constant.
constexpr int pow(int base, int power) noexcept
{
    int result = 1;
    for(int i=0; i<power; i++)
    {
        result = result * base;
    }

    return result;
}

constexpr int cmds = 10;

//Initialization at compile time
std::array<int,pow(3,cmds)> data;


// ===========================================================

//For a method to be executed at runtime , it must :
//  - Have a return type != void
//  - don't modify the internal state of the object
//  - arguments should be known at compile time

//Maybe constructor makes an exception from this rules 

class Point
{

public:
    constexpr Point(double xVal=0 , double yVal=0) noexcept : x(xVal) , y(yVal)
    {}

    constexpr double getX() const  noexcept 
    {
        return x;
    }

    constexpr double getY() const  noexcept 
    {
        return y;
    }

    constexpr void setValueX(double xArg) noexcept
    {
        x = xArg;
    }


    double x , y;
};

constexpr Point midPoint(const Point& p1 , const Point& p2)
{
    double r = 0.0;
    double r2 = 0.0;

    r = ( p1.getX() + p2.getX() ) /2 ;
    r2 = ( p1.getY() + p2.getY() ) /2 ;

    return Point {r,r2};
}


int main()
{
    constexpr int local = 3;
    char array[local];

    std::array<int,local> buffer;

    int result = sum(2,6);


    constexpr Point p(3.4, 5.7);
    std::cout <<"Jerry and Tom ! " << std::endl;
    //p.setValueX(2.33321);     Error const Point can't be changed
    

    // =================================================== 

    constexpr Point p2(4.2 , 1.3);
    //The midpoint calculation is done at compile time and the result is placed    
    constexpr Point pr = midPoint(p,p2);
    
    std::cout << pr.getX() << std::endl;

}

