#include <iostream>
#include <string>
#include <vector>
#include <memory>


//Use const_iterator whenenver possible ! 


std::vector<int> v {12,3,4,5,6,7,8,98};


void f()
{

    throw 20;
}


int main()
{
    //cbegin() returns const iterator 
    auto it = std::find(v.cbegin(),v.cend(), 8);
    if(it != v.cend())
    {
        std::cout << " Found it ! " << std::endl;
        v.insert(it, 0xff);
    }

    for(auto i=v.cbegin(); i != v.cend(); i++)
        std::cout << *i << std::endl;


    try
    {
        f();
    }
    catch(int i)
    {
        std::cout <<"Catched : " << i << std::endl;
    }

    return 0;
}
