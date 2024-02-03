#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;


template<typename T1=float, typename T2=int>
struct test_struct 
{
    static constexpr int value = 0;
};

template<typename T1>
struct test_struct<T1, void>
{
    static constexpr int value = 1;
};

// First argument is double, the second one should be deduced or replaced with default if exists
template<typename T2>
struct test_struct<double, T2>
{
    static constexpr int value = 2;
};

template<typename T2>
struct test_struct<char, T2>
{
    static constexpr bool value = true;
};




int main()
{
// By default compiler will generate test_struct implementation for each of the requested pair of types.
// In case not all the arguments are specified, they will be replaced by default arguments
// If there is a specialization for at least one argument defined by user, that one will be picked and
// if one or more arguments are not specified, again will use the default values.

    test_struct<double>::value;	
//    template<>    Generic version
//    struct test_struct<double, int>
//    {
//     inline static constexpr const bool value = false;
//    };

    test_struct<char>::value;	
//    template<>    Specialization
//    struct test_struct<char, int>
//    {
//     inline static constexpr const bool value = true;
//    };
  
  
  	test_struct<double,float>::value;
//	 template<>     Generic version
//	 struct test_struct<double, float>
//	 {
//    inline static constexpr const bool value = false;
//	 };
  
  	test_struct<>::value;
//  template<typename T1=float, typename T2=int>
//  struct test_struct 
//  {
//      static constexpr bool value = false;
//  };  
  
// 	 test_struct<char,void>::value;		Ambiguous specialization 

    return 0;
}