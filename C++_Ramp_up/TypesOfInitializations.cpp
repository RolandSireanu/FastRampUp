// default-initialization – If T is a class, the default constructor is called; if it’s an array, each element is default-initialized; otherwise, no initialization is done, resulting in indeterminate values. [ cppref1 ]
// value-initialization – If T is a class, the object is default-initialized (after being zero-initialized if T ’s default constructor is not user-provided/deleted); if it’s an array, each element is value-initialized; otherwise, the object is zero-initialized. [ cppref2 ]
// zero-initialization – Applied to static and thread-local variables before any other initialization. If T is scalar (arithmetic, pointer, enum), it is initialized from 0 ; if it’s a class type, all base classes and data members are zero-initialized; if it’s an array, each element is zero-initialized. [ cppref3 ]

// T global;    //zero-initialization, then
//              // default-initialization
// void foo() {
//   T i;       //default-initialization
//   T j{};     //value-initialization (C++11)
//   T k = T(); //value-initialization
//   T l = T{}; //value-initialization (C++11)
//   T m();     //function-declaration
//   new T;     //default-initialization
//   new T();   //value-initialization
//   new T{};   //value-initialization (C++11)
// }

// //t is value-initialized
// struct A { T t; A() : t() {} };
// //t is value-initialized (C++11)
// struct B { T t; B() : t{} {} }; 
// //t is default-initialized
// struct C { T t; C()       {} };

class Conv 
{
    public:

    int size;
};

class Mult 
{
    public:
    Mult() = default;
    int size;
};  

class Reshape 
{
    public:
    Reshape() {};
    int size;
};  

int main()
{
    Conv conv;      //undefined value for "size"
    Conv conv{};    //size is zero initialized because no user default constructor is provided

    Mult mult;      // undefined value for size 
    Mult mult{};    // size is zero initialized

    Reshape reshape;    // undef value for size
    Reshape reshape{};  // undef value for size because user has already provided the default constructor

}