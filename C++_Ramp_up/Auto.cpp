#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>
//Using auto your variables will always be initialized
//An auto declared variable holding a closure will have the exact same type as the closure so will use
//only as much memory as closure needs.
//A variable of std::function holding a closure will reserve more memory because std::function has a fixed
//type for every signature , plus the memory required by closure

using uptr = std::unique_ptr<int>;

// When auto can fail to deduce the right type?
std::vector<bool> f()
{
    return {true,false,true};
}

// Vector of bool is a bitfield, so the [] will return a reference to a proxy object
auto refToTempObject = f()[0];


int main()
{


    auto f = [](std::unique_ptr<int>& a, std::unique_ptr<int>& b) -> bool{
        return *a > *b;
    };

    auto f14 = [](const auto& a, const auto& b) -> bool {
        return *a > *b;
    };

    std::unique_ptr<int> p1(new int(28));
    std::unique_ptr<int> p2(new int(24));
    if(f(p1,p2))
        std::cout << "Works ! " << std::endl;

    if(f14(p1,p2))
        std::cout << "Works in 14 also ! " << std::endl;

    //===============================================================================
    std::function<bool(const uptr&, const uptr&)> fo = [](const uptr& a, const uptr& b){
        return *a > *b;
    };

    if(fo(p1,p2))
        std::cout << "Works with std::function also " << std::endl;

    std::cout << "Size of std::function = " << sizeof(fo) << std::endl;
    std::cout << "Size of auto = " << sizeof(f) << std::endl;
    std::cout << sizeof(f14) << std::endl;
    // ===============================================================================


    {
        using namespace std;

        vector<int> v {2,4,6,8};
        unsigned usize = v.size(); //type of usize is uint32b , but on Windows 64 bit mahine v.size
        // return vector<int>::size_type which is 64 and unsigned is still 32
        auto asize = v.size(); // Now asize is vector<int>::size_type whatever dimension will have

    }


    //Using auto instead of declared type assures as of using the right type.
    //For example , value_type of unordered_map , is std::pair<const string key, int value> if we are using
    // std::pair<string key , int value> compiler will create a temp object for every iteration and set the ref to it.
    {
        std::unordered_map<std::string, int> m;

        m.emplace("Roland",28);
        using value =std::unordered_map<std::string, int>::value_type;
        for(const value& v : m)
        {
            std::cout << std::get<1>(v) << std::endl;
            std::cout << std::get<0>(v) << std::endl;
        }

        // for (const std::pair<std::string, int>& v : m)
        // {
        //     std::cout << std::get<0>(v) << std::endl;
        // }
    }



    return 0;
}