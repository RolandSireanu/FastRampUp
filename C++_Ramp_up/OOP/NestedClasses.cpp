#include <string>
#include <iostream>

class A {

    //By defining a nested class you change nothing in terms of members visibility 
    //It is just a method of encapsulation , similar with a namespace
    class Nested {

    };
};


//Inner classes has access to private members outter class
class Animal {
    public:
    class InnerAnimal {

        public :
            void tellMeAnimalsName(const Animal& a) {
                std::cout << a.name << std::endl;
            }
    };

    private:
    std::string name = "Dixi";

};


int main()
{

    Animal a;
    Animal::InnerAnimal ia;
    ia.tellMeAnimalsName(a);

    return 0;
}