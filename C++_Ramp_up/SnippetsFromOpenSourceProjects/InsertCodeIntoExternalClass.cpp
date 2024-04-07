#include <iostream>
#include <memory>
#include <string>
#include <type_traits>


class Animal
{
public:
    Animal(int arg, const std::string& arg2) {}

    virtual ~Animal() {std::cout << "Destroying Animal object " << std::endl; }
};


template <typename T>
class Container
{

    public:

    class Wrapper;

    template<typename... Args>
    std::unique_ptr<Wrapper> build_object(Args&&... args)
    {
        return std::make_unique<Wrapper>(std::forward<Args>(args)...);
    }


    class Wrapper : public T
    {
        public:
        template<typename... Args>
        Wrapper(Args&&... args) : T(std::forward<Args>(args)...) {}

        virtual ~Wrapper() { std::cout << "Code inserted in your class " << std::endl; }
    };

};


int main()
{
    Container<Animal> c;
    std::string argument{"Cat"};
    auto ptr = c.build_object(23, argument);
}