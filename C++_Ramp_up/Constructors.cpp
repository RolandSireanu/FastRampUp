#include <cstdio>
#include <iostream>
using namespace std;

class Object
{
    public:
    Object() { cout << "Default constructor " << endl; }
    Object(const Object&) { cout << "Copy constructor " << endl; }
    Object(const Object&&) { cout << "Move constructor " << endl; }
    Object& operator=(const Object&) { cout << "Copy asigment operator" << endl; }
    Object& operator=(const Object&&) { cout << "Move asigment operator" << endl; }
    bool operator=(Object&) { cout << "Bool operator "<<endl; return true; }
    Object(int a) { cout << "Converting constructor 1 int" << endl; }
    Object(int a, int b, int c) { cout << "Converting constructor 3 int args" << endl; }
    Object(std::initializer_list<int> arg) { cout <<"Constructor initializer_list " << endl; }

};

//explicit = it can't be used for implicit conversions or copy initializations

class ExplicitObject 
{
    public:
    // ExplicitObject() { cout << "Default constructor " << endl; }
    explicit ExplicitObject(ExplicitObject&) { cout << "Copy constructor " << endl; }
    // ExplicitObject(ExplicitObject&&) { cout << "Move constructor " << endl; }
    // ExplicitObject& operator=(ExplicitObject&) { cout << "Copy constructor operator" << endl; }
    // ExplicitObject& operator=(ExplicitObject&&) { cout << "Move constructor operator" << endl; }
    explicit ExplicitObject(int a) { cout << "Converting constructor 1 int " << endl; }
};


//Default constructor generations
//If a copy constructor || copy assigment operator is defined , compiler
//will not generate move constructor && mode asigment operator
//If user defined constructor is implemented, compiler will not generateda  default constructor

//default keyword is used to force the compiler in generating constructors which are
//by default not generated due to the current context.

class DefaultObject
{
    public:    
    DefaultObject(int a) { cout <<"Converting constructor int"<< endl; }
    //No default constructor is generated until now...

    //Now we force the compiler to generate a default constructor
    DefaultObject() = default;

    //No copy constructor is generated until now ...
    DefaultObject(DefaultObject&& arg) { cout <<"Move constructor called "<< endl; }

    //Now we force the compiler to generate a default constructor
    DefaultObject(DefaultObject& arg) = default;
    //And now we force the compiler to delete the copy assigment operator
    DefaultObject& operator=(DefaultObject& ) = delete;
};

// 
int main()
{

    cout << " ============= When different constructors are called ============ " << endl;
    Object o1;                          // Default constructor
    Object o2(o1);                      // direct-initialization - Copy constructor
    Object o3 = o1;                     // copy-initialization - Copy constructor
    o2 = o3;                            // Copy assigment operator
    o2 = Object();                      // Move assigment operator
    Object o5{};                        // Default constructor
    Object o6(0, 0, 0);                 // Converting constructor 3 ints
    Object o7 {0, 0, 0};                // Constructor initializer_list

    cout << " ============= Converting constructors in play ============ " << endl;

    o6 = {1,1,1};                       // Build Object with initializer_list constructor, call move constructor to init o6    
    o6 = 2;                             // Build Object with converting constructor int, and call move to init o6


    cout << " ============= Explicit constructors ============ " << endl;
    ExplicitObject e1(1);
    // ExplicitObject e2 = 1;      Error , copy initialization doesn't consider explicit converting constructors
    // ExplicitObject e2 = e1;     Error , copy initialization doesn't consider explicit copy constructor
    ExplicitObject e2(e1);          // Direct initialization is ok with explicit copy constructors

    cout << " ============= Default/Delete constructors ============ " << endl;
    DefaultObject object1(3);
    DefaultObject object2;

    DefaultObject object3 (object2);
    // object3 = object2;          //Deleted copy assigment operator

    return 0;
}

