#include <initializer_list>
#include <vector>
#include <iostream>


//Decltype just parrot back the exact type of expression 


//Auto specified that type should be deduced , and decltype specifies
//that type should be deduced based on decltype rules 
template<typename ContainerType>
decltype(auto) access(ContainerType&& c, int index)
{
    return std::forward<ContainerType>(c)[index];
}


int main()
{
    std::vector<int> v = {1,2,3,4,5};


    std::cout << access(v,2) << std::endl;

    //Modifying the container send to template function
    access(v,0) = 0xFF;

    //Sending lvalue to template function
    std::cout << access(v,0) << std::endl;

    //Sending rvalue to template function
    std::cout << access(std::vector<int>{6,7,8},1) << std::endl;

    // ===================================================================

    int temp = 0x11;
    const int& r = temp;

    auto av = r;                //av will be int 
    decltype(auto) dav = r;     //dav will be const int&


    return 0;
}