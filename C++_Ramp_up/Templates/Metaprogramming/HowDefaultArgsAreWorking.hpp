#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

template<typename T = float>
class Car
{
public:
  	Car() {}
    Car(T arg){}
};

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
    static constexpr int value = 3;
};




int main()
{
// By default compiler will generate test_struct implementation for each of the requested pair of types.
// In case not all the arguments are specified, they will be replaced by default arguments
// If there is a specialization for at least one argument defined by user, that one will be picked and
// if one or more arguments are not specified, again will use the default values.

    std::cout << test_struct<double>::value << "\n";
//    template<>
//    struct test_struct<double, int>
//    {
//     static constexpr int value = 2;
//    };

    std::cout << test_struct<char>::value << "\n";
//    template<>
//    struct test_struct<char, int>
//    {
//     static constexpr int value = 3;
//    };
  
  
  	std::cout << test_struct<double,float>::value << "\n";
//	 template<>
//	 struct test_struct<double, float>
//	 {
//    static constexpr int value = 2;
//	 };
  
  	std::cout << test_struct<>::value << "\n";
//  template<typename T1=float, typename T2=int>
//  struct test_struct 
//  {
//      static constexpr int value = 0;
//  };  
  
	//  test_struct<char,void>::value;		 Ambiguous specialization 
	
    // Car<int> myCar;
    Car myCar{23};	
    
    // Car<float> myCar2;
  	Car myCar2;

    return 0;
}