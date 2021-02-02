#include <iostream>
#include <vector>
#include <atomic>
#include <memory>
#include <mutex>


class Widget
{};


//Using nullptr instead of NULL or 0
//By using null or 0 for comparing with pointer type you may be surprised by the
//overloaded functions . Example : 

void f(int a) {}
void f(int* a) {}

//The advantage of nullptr is that it doesn't have an integral type , so it can't be 
//bind to an int. 
//Nullptr is a pointer of all types ! 


// The most important usage of nullptr is with template types 
int f1(std::shared_ptr<Widget> spw){}
float f2(std::unique_ptr<Widget> upw){}
bool f3(Widget* pw){}

//=============================Usage of templates ==========================================
template<typename T, typename Function>
decltype(auto) proxy(std::mutex& m, T arg, Function f)
{
    using TGuardMutex = std::lock_guard<std::mutex>;

    TGuardMutex guard(m);
    return f(arg);
}


int main()
{
    f(0);           // will always call f(int)
    // f(NULL);     will not compile
    f(nullptr);     //will call f(int*)
    //===========================================================

    std::mutex m1, m2, m3;
    using TGuardMutex = std::lock_guard<std::mutex>;


    //Compiler creates a temporary shared_ptr object with nullptr as type
    {
        TGuardMutex guard(m1);
        auto result = f1(0);
    }

    //Compiler creates a temporary shared_ptr object with nullptr as type
    {
        TGuardMutex guard(m2);
        auto result = f2(NULL);
    }

    //Compiler just call the f3 function with nullpt , no temp object is created
    {
        TGuardMutex guard(m3);
        auto result = f3(nullptr);
    }

    // Usage of templates to avoid this implicit conversions from 0 or NULL to nullptr 
    // by creating temp objects. Template type deduction kicks in to figure out the argument type ! 

    //Can't convert int to shared_ptr<Widget>
     //proxy(m1, 0, f1);  Compiler error due to "0" arg
    

    //Can't convert NULL to unique_ptr<Widget>
    //proxy(m2, NULL, f2);

    proxy(m3, nullptr, f3);

    return 0;
}