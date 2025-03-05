#include <iostream>
#include <memory>
using namespace std;

// Covariant return type means that for a virtual function you can a narrower return type in the derived classes


class Computer
{

};

class Laptop : public Computer {};

class ComputerFactory
{
public:
    virtual Computer* produce() { return nullptr;}    
};

class LaptopFactory : public ComputerFactory
{
public:
    // It overrides the "produce" method in the base class but returns a narrower type
    Laptop* produce() override {return nullptr;}
};


int main()
{

    return 0;
}