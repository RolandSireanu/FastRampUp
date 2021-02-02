#include <iostream>
#include <string>

//Declare overriding functions as overriden
//It is very easy to go wront with function overriding in class hierarchy
//In order for a function to be overriden by the derived class , some
//requirement must be met : 
    // • The base class function must be virtual.
    // • The base and derived function names must be identical (except in the case of
    // destructors).
    // • The parameter types of the base and derived functions must be identical.
    // • The constness of the base and derived functions must be identical.
    // • The return types and exception specifications of the base and derived functions
    // must be compatible.
    // • Function reference qualifiers must be identical
class Base {
    public:
        virtual void mf1() const;
        virtual void mf2(int x);
        virtual void mf3() &;
        void mf4() const;
};

// class Derived: public Base {
//     public:
//         virtual void mf1();
//         virtual void mf2(unsigned int x);
//         virtual void mf3() &&;
//         void mf4() const;
// };

//There is not overriding in code above ! 
//That trap is that code compiles

//By marking them as override a compiler warning will be raise 
// in case of the override process can't take place ! 
class Derived: public Base {
    public:
        virtual void mf1() override;
        virtual void mf2(unsigned int x) override;
        virtual void mf3() && override;
        void mf4() const override;
};



int main()
{


    return 0;
}