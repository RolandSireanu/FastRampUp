#include <iostream>
#include <string>


class MyClass
{
    public:
        MyClass() = default;
        //Delete methods instead of declaring them private like in C++98
        MyClass(const MyClass&) = delete;
        MyClass& operator=(const MyClass&) = delete;

        template<typename T>
        void method(T arg){}
};

//You can delete also function not just methods 
bool isMyLuckyNumber(int arg){ return true;}
bool isMyLuckyNumber(float arg) = delete;
bool isMyLuckyNumber(std::string arg) = delete;


//Delete can be use in order to restrict types in a template
template<typename T>
void f(T* arg);

//Let's say you don't want to process void* and char*

template<>
void f(void*) = delete;

template<>
void f(char*) = delete;

//You can delete also methods specialization 
template<>
void MyClass::method(int) = delete;





int main()
{
    // isMyLuckyNumber("alabala");   Error , use of deleted function
    void* p;
    // f(p);        Error , used of deleted function 

    MyClass mc;
    // mc.method(23);   Error , used of deleted function

    return 0;
}