#include <iostream>
#include <vector>
#include <atomic>
#include <memory>
#include <type_traits>
#include <list>

// Prefer using instead of typedef for aliases
// Using them inside of templates brings a significat difference between the two expressions.

class Widget {};

template<typename T>
using MyList = std::list<T>;
MyList<Widget> l;



//This is because typedef can't work with templates
template<typename T>
struct MyListStruct
{
    typedef std::list<T> type;
};

MyListStruct<Widget>::type ll;

template<typename T>
class Container
{
    //When compiler see MyListStruct<T>::type . it can't be sure that is a type , it may be a data member of MyListStruct class 
    typename MyListStruct<T>::type ml;      //MyListStruct<T>::type is a dependent type , of a template parameter
                                            //Names of a dependent type must be preceded by typename

    //When compiler see MyList , he knows that is an alias def so it must be a type => non dependent type , typename not required
    MyList<T> mySimpleList;                 //By utilizing "using" instead of typedef , the ::type disappear and also the typename
};


// Improving type_traits with aliases
//All the type_traits inside the standard library are written with typedef so this implies that you have to use the typename (dependent type)
using constint = const int;
typename std::remove_const<constint>::type w;

template<typename T>
using rc = typename std::remove_const<T>::type;

rc<const int> v ;

int main()
{
    w = 0x00;
    v = 0xff;

    return 0;
}