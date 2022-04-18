#include <iostream>
using namespace std;

//Mutable keyword allow even the const declared function to change
//the internal state
class A
{
    public:
        void set_flag(bool arg) const
        {
            is_ready = arg;
        }
    private:
        mutable bool is_ready = false;
};


int main()
{
    int var = 10;
    //The second use of mutable keyword is in conjuction with lambda
    //If lambda should change the captured variables, the mutable keyword in mandatory

    auto lambda = [=]() mutable { var = var + 1; };
}