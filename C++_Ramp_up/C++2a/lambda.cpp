
// ===================================== Capturing of "this" pointer in lambda ==============================

// Before C++20 the "this" pointer was captured by default in lambda (as pointer) when using the default capture mode "="
class Laptop
{
public:
    void f()
    {
        auto lambda = [=](int arg){return this->number *arg; };
    }

  	int number;
};

// ===> Translated to 
// class Laptop
// {
  
//   public: 
//   inline void f()
//   {
        
//     class __lambda_11_23
//     {
//       public: 
//       inline int operator()(int arg) const
//       {
//         return __this->number * arg;
//       }
      
//       private: 
//       Laptop * __this;
//       public: 
//       // inline /*constexpr */ __lambda_11_23(__lambda_11_23 &&) noexcept = default;
//       __lambda_11_23(Laptop * _this)
//       : __this{_this}
//       {}
      
//     };
    
//     __lambda_11_23 lambda = __lambda_11_23(__lambda_11_23{this});
//   }
  
//   int number;
// };


// ============================================================================================
// Starting with C++20 implicit capture of 'this' with a capture default of '=' is deprecated
// You need to specify explicity the capture of "this" using "*this" for deep copy or "this" for shallow copy
auto lambda = [=, this](int arg){return this->number *arg; };
auto lambda = [=, *this](int arg){return this->number *arg; };

// ============================================================================================


#include <iostream>
#include <tuple>
#include <functional>
#include <array>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <set>

struct Book
{
    std::string title;
    std::string author;
};

struct Price
{
    double price;
};

// ========================= BooksSortedByTitle version 1 ==========================================

auto comparator = [](const Book& lhs, const Book& rhs) -> bool { return lhs.title > rhs.title; };

template<typename V>
using BooksSortedByTitle = std::map<Book,
                                    V,
                                    decltype(comparator)
                                    >;

// ========================= BooksSortedByTitle version 2 ==========================================

using cmpType = decltype([](const Book& lhs, const Book& rhs) -> bool { return lhs.title > rhs.title; });
template<typename V>
using BooksSortedByTitle2 = std::map<Book,
                                    V,
                                    cmpType
                                    >;

int main()
{

    const Book tempBook {"AmintiriCopilarie", "IonCreanga"};

    BooksSortedByTitle<Price> books {
        {{tempBook, Price{2.2}}},
        comparator
    };

    // Unfortunately the user has to specify the "comparator"
    // The std::map can default construct an object of
    // the compare-type if we provide no custom compare function.
    // In C++17 and before, lambdas are not default-constructible. The standard defines
    // them with a deleted default constructor. This restriction is lifted in C++20. We can
    // drop naming the compare function from the constructor’s argument list. With that,
    // users no longer need to know the name of the compare function and don’t have to
    // type it.

    //  This works starting with C++20
    //  The std::map can default construct an object of type "decltype(comparator)"
    BooksSortedByTitle<Price> books2 {
        {tempBook, Price{2.2}}
    };


    // Ok but if this works, than we never needed a callable right?
    // Let's eliminate the instantiation of lambda "comparator" with "BooksSortedByTitle2"
     BooksSortedByTitle2<Price> _books_ {
        {tempBook, Price{2.2}}
    };

    std::vector<int> v {4,3,6,1,9,0,3};
    std::sort(v.begin(), v.end());
    for(const auto& e : v)
        std::cout << e << " \n";


    // The same for the std::set, you don;t need a callable anymore, only a type
    // Std::set will instantiate internally a callable of provided type
    std::set<int, decltype([](int a, int b){return a > b; })> s;

    return 0;
}