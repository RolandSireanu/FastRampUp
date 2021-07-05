#include <iostream>
#include <vector>
using namespace std;

//Rule of five 
//  1.Declaring move constructor , move assigment operator , even as 
//default or delete , will supres the implicitly generated copy constructor ,
//copy asigment operator.
//  2.Declaring copy constructor , copy assigment operator or destructor 
//even as default or delete will supress implicitly generated move constructor/assigment operator

class RuleOfFive_1 
{
    public:
        //If we declare any of these 3 constructors / operations,
        //the move counterparts will not be generated anymore
        RuleOfFive_1(const RuleOfFive_1&) = default;
        //RuleOfFive_1& operator=(const RuleOfFive_1&) = default;
        //~RuleOfFive_1() = default;

        //If move constructor or assigment operator is declared 
        //Copy constructor and copy assigment operator will not be generated anymore
        RuleOfFive_1(RuleOfFive_1&& );

};

// So as soon as any of these are declared, the others should all be declared to avoid unwanted effects 
// like turning all potential moves into more expensive copies, or making a class move-only.


//Rule of three
//If you have defined copy constructor / assigment operator / destructor 
//most likely you have to define them all 


class A 
{
    public:
    A() = default;
    A(const A& ) { cout << "A is copied ! \n"; }
    A(A&&) { cout << "A is moved ! \n"; }
};


//Example for rule of five 
//"a" will be copied , not moved !

class Base 
{
    public:
        //Because we have defined custom destructor => no implicit move constructor
        //or move assigment operation is generated. 
        virtual ~Base() = default;
    
        A a;
};


int main()
{
    Base b1;
    Base b2 = move(b1);


    return 0;
}

