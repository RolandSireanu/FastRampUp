#include <iostream>
using namespace std;

class Flag {

    public:
        Flag() : flag{false} {}        //Default constructor
        //"explicit" should receive only a bool , no additional conv will be done
        Flag(const Flag& arg) { flag = arg.flag; }    //Copy constructor
        Flag(Flag&& arg) = delete;              //Move constructor
        //This can bind to an lvalue or rvalue 
        Flag& operator=(const Flag& arg) { return *this; } //Copy asigment operator   
        Flag& operator=(Flag&& arg) = delete;   //Move asigment operator

        explicit Flag(bool arg){ 
            flag = arg;
            cout << "Flag constructor (bool) " << endl;    
        }

        bool operator||(const Flag& arg) {
            return this->flag || arg.flag;
        }

        bool operator&&(const Flag& arg) {
            return this->flag && arg.flag;
        }

        //Pre increment operator
        Flag operator++()
        {
            flag = !flag;
            return *this;
        }

        Flag operator++(int)
        {
            bool temp = flag;
            flag = !flag;
            //RVO
            return Flag(temp);
        }

        operator bool() { return flag; }
        operator int() { return flag ? 1 : 0; }

    private:
        bool flag;
};


int main()
{
    Flag f1;
    Flag f2(true);

    ++f1;
    cout << boolalpha << (f1 && f2) << endl;

    //Because we have declared copy constructor as explicit we can;t build
    //the object like this.
    Flag f(3);


    return 0;
}