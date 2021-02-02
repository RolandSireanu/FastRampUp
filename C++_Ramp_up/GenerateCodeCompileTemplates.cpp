#include <iostream>
#include <memory>
#include <type_traits>
#include <list>
#include <string>


template<unsigned a , unsigned b>
unsigned f()
{
    return a + b;
}


template<unsigned b0, unsigned b1, unsigned b2, unsigned b3>
unsigned int buildMask()
{
    static_assert(b0 < 2);
    static_assert(b1 < 2);
    static_assert(b2 < 2);
    static_assert(b3 < 2);

    return ((b0<<0) | (b1<<1) | (b2<<2) | (b3<<3));
    
        
}



int main()
{
    f<2,3>();
    std::cout << buildMask<1,1,1,1>() << std::endl;
    return 0;
}