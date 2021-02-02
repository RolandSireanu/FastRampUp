#include <iostream>
#include <tuple>
#include <atomic>
#include <memory>
#include <type_traits>
#include <list>
#include <string>

//Prefer scoped enums to unscoped enums

//This is in unscoped enum 
// blue white and red are in the same scope as Colors
enum Colors {blue, white, red};
// auto blue  = 2.3f;      Error , blue is already in the scope ! 
//Enum values leaks into the scope , and polute it 

//This is a scoped enum , values blue white and red are scoped to ClassColors
enum class ClassColors: std::uint8_t {blue, white, red};

//Beside poluting the namespace , unscoped enums are not strongly typed. Implicitly convert to integral types

//Scoped enums can be forward declared 
enum class ForwardDeclarationEnum;


//The only place where unscoped enums are prefered is in tuples usage

std::tuple<std::string, int> t;


int main()
{

    int c = blue;
    ClassColors cc = ClassColors::blue;

    enum Members {name , age};
    t = std::make_tuple("Roland" , 28);
    //Conversion between Members are size_t is done implicitly
    std::cout << std::get<name>(t) << std::endl;

    return 0;
}