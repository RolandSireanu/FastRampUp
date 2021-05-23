#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int x = 0xaa;

class Animal 
{
    public:
    void tellMe(){
        
        //Lambda defined in class can access private members "name"
        auto l = [&]{ cout << this->name << endl; };
        l();
    }

    private:
    std::string name = "Labus";
};

int main()
{

    int y = 0xff;

    //Lambda can access global variables but not local ones without capturing them first
    []{cout << x << endl;}();

    //Function pointers can call lambdas functions
    auto call = []{ return 22; };
    int (*fp)() = call;
    cout << fp() << endl;

    //Mark mutable for changing generated class state 
    auto changingState = [=] mutable { y++; };

    //References are not considered class members , so changing them doesn't require
    //mutable keyword , because generated class state doesn't change with reference
    // changes
    auto notChangingState = [&] { y++; };

    //From c++14 we can use auto in lambda's arguments
    auto autoArgument = [](auto& arg) { return arg * 2; };

    //From c++14 we can define a private member of lambda in capture by initializing a 
    //non existing variable
    auto declareMemberInCapture = [base = 2](int exponent) { return pow(base,exponent);};
    cout << declareMemberInCapture(3) << endl;

    return 0;
}