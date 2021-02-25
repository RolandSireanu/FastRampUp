#include <iostream>
using namespace std;

//Virtual destructor
//Whenever you have polimorphism you should use a virtual destructor
//delete base , will call destructor just for base class not for derived one
//if base class destructor is not marked as virtual

class Base
{
public:
    Base() {cout <<"Base constructor " << endl; }
    virtual ~Base() {cout <<"Base destructor " <<endl; }

    virtual void callMe()
    {
        cout <<"CallMe Base " << endl;
    }
};

class Derived : public Base
{
public:
    Derived() {cout <<"Derived constructor " << endl; }
    ~Derived() {cout <<"Derived destructor " <<endl; }

    void callMe() override
    {
        cout << "CallMe Derived" << endl;
    }
};

int main()
{

    Base* b = new Derived();
    delete b;

    return 0;
}