#include <iostream>
using namespace std;

// Overload resolution uses a ranking system to find the best match
// The ranking system is based on the conversion from argument type to param type
// There are three levels in the ranking system from cheap to expensive conv:
    // -no conversion 
    // array to pointer
    // qualification conversion
    
    //integral promotion
    //floating-point promotion

    //integral conversion
    //floating point conversion
    //pointer conversion
    //boolean conversion

// Qualified vs unqualified names
    // A name appearing ah the right of :: , . , -> is a qualified name
    // A name that isn't qualified is unqualified
    // string::assign       assign is qualified, string is unquallified

// Lookup for qualified names is fairly simple:
    // For S::n look for n into S whre S can be a namespace or class
    // x.n look for n into object x

// Lookup for unqualified name:
//Unqualified name n appear in a non-member function f at namespace scope
    // Look into the local scope (the block where name appear)
    // Work outward to the scope of f 
    // Look into namespace of f
    // Work outward to the global scope
    // Try ADL


// Overload resolution process:
// As a main guidline, how the candidates are ranked inside the overload set:
// 1. The non template function are choosen first
// 2. The specialization are choosen second (even for lvalue rvalue)
// 3. Next are the templates (const T& binds to lvalue and T&& bind only to rvalues)

class Animal
{
public:
    Animal() {}
    Animal(const Animal&) {}
    Animal(Animal&&) {}
    Animal& operator=(const Animal&) {}
    Animal& operator=(Animal&&) {}
};

class Cage
{
public:
    Cage() {}
    Cage(const Cage&) {}
    Cage(Cage&&) {}
    Cage& operator=(const Cage&) {}
    Cage& operator=(Cage&&) {}
};

class Food
{
public:
    Food() {}
    Food(const Food&) {}
    Food(Food&&) {}
    Food& operator=(const Food&) {}
    Food& operator=(Food&&) {}
};

template<typename T>
void push(T& arg) { std::cout << "template push(T&)" << std::endl;}

template<typename T>
void push(T&& arg) { std::cout << "template push(T&&)" << std::endl;}
 
template<>
void push<Animal>(Animal&&) { std::cout << "push(Animal&&)" << std::endl;}

template<>
void push<Food>(Food& arg) { std::cout << "template<> push(Food&)" << std::endl;}

template<>
void push<Cage>(Cage& arg) { std::cout << "template<> push(Cage&)" << std::endl;}

void push(Cage arg) {std::cout << "push(Cage)" << std::endl;}


int main()
{
    Animal a;
    Cage c;
    Food f;

    push(a);            // template push(T&)
    push(Animal{});     // push(Animal&&)
    push(c);            // push(Cage)
    push(Cage{});       // push(Cage)
    push(f);            // template<> push(Food&)
    push(Food{});       // template push(T&&)

    return 0;
}