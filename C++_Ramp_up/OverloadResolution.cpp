#include <iostream>
using namespace std;

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