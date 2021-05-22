

//By default in struct every element is public
//Used in c++ for simple cases , in close keeping to the C syntax
struct MyStruct 
{
    //public:
    int a;
    char b;
};


//Implicitly defined functions
//This functions have default implementation as long as the class members are trivial initializable
//If we exchange "int a" with "const int a" default constructor will not be implicitlly definded
class MyClass
{
    public:

        //Functions defined implicitly by the compiler in a C++ class :
        MyClass();                              //Default constructor
        MyClass(const MyClass& );               //Copy constructor
        MyClass(MyClass&& );                    //Move constructor

        MyClass& operator=(const MyClass& );    //Copy asigment operator
        MyClass& operator=(const MyClass&& );    //Move asigment operator

        MyClass* operator&();                   //Address of operator

        ~MyClass();                             //Default destructor

        int a;
        char b;
};