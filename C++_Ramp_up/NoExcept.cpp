#include <iostream>
#include <utility>

//By declaring a function noexcept , the compiler can better 
//optimized the code , knowing that stack unwinding will not be 
//necessary

int function(int a , int b )    noexcept
{
    return a + b;
}

int main()
{
    function(2,5);
}

