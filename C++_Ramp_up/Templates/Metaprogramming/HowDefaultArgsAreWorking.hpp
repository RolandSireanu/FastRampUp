#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;


template<typename T1, typename T2=int>
struct test_struct 
{
    static constexpr bool value = false;
};


template<typename T1>
struct test_struct<T1, void>
{
    static constexpr bool value = true;
};


int main()
{
// By default compiler will generate test_struct representations for each
// of the below types.
// ===== Step 1: Compiler generates specializations for every requested types
// 			   If the second argument is not specified, the default one "int" is used, otherwise
// 			   T2 is used (see <double,float> scenario)
// 
    test_struct<float>::value;	
//    template<>
//    struct test_struct<float, int>
//    {
//     inline static constexpr const bool value = false;
//    };
  
    test_struct<int>::value;
//    template<>
//    struct test_struct<int, int>
//    {
//     inline static constexpr const bool value = false;
//    };
  
    test_struct<double>::value;
//    template<>
//    struct test_struct<double, int>
//    {
//     inline static constexpr const bool value = false;
//    };
  
  	test_struct<double,float>::value;
//	 template<>
//	 struct test_struct<double, float>
//	 {
//    inline static constexpr const bool value = false;
//	 };
  
// ===== Step 2: If any of the specialization already exists, used them and don't generate
  // new ones. Like above, specialization for <any_type, void> was specified by the user => use it !
  	test_struct<char,void>::value;
//   template<>
//	 struct test_struct<char, void>
//	 {
//   	inline static constexpr const bool value = true;
//	 };

    return 0;
}