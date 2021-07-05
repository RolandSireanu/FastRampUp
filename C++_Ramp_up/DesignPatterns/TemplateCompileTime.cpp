#include <iostream>
#include <utility>
#include <functional>
#include <string>
#include <unordered_map>
using namespace std;

enum class emulationMethod : unsigned 
{
    ARM,
    COMODORE64
};

class base
{
    public:
        virtual void execute() = 0;
        virtual pair<emulationMethod, function<void(void)> > getImpl() = 0;
        void run()
        {
            getImpl().second();
        }
        // void run(emulationMethod em) 
        // {
        //     auto it = getImpl(em);
        //     it.second();
        // }   
};

class ArmEmulation : public base
{
    public:
        static constexpr emulationMethod type = emulationMethod::ARM;
        void execute() 
        {
            implementation();
        }

        void implementation() { cout << "ArmEmulation ! \n"; }
};

constexpr emulationMethod ArmEmulation::type;


class ComodoreEmulation : public base
{
    public:
        static constexpr emulationMethod type = emulationMethod::COMODORE64;

        void execute() 
        {
            implementation();
        }

        void implementation() { cout << "ComodoreEmulation ! \n"; }
};

constexpr emulationMethod ComodoreEmulation::type;

template<typename T>
class Bind : public T
{
    public:

    Bind() : T{} 
    {
        impls.emplace(T::type, [this](){ T::execute(); });
    }

    pair<emulationMethod, function<void(void)> > getImpl()
    {
        auto it = impls.find(T::type);
        if(it == impls.end())
        {
            cout << "Implementation not found ! \n";
            return *impls.begin();
        }
        else
            return *it; 
    }

    unordered_map<emulationMethod, function<void(void)> > impls;

};

int main()
{

    Bind<ComodoreEmulation> b;
    Bind<ArmEmulation> b2;
    b.run();
    b2.run();




    return 0;
}
