#include <iostream>
using namespace std;

//Friends functions and classes 

class A
{
    public :
        A(int argA, int argB) : a{argA}, b{argB} {}

    private:
        friend class FriendClass;
        friend void showPrivate(const A& arg);

        int a;
        int b;
};


class FriendClass 
{
    public:
        void showPrivateMembers(const A& arg) {
            cout << arg.a << endl;
        }
};

void showPrivate(const A& arg)
{
    cout << arg.b << endl;
}

int main()
{
    A objA(3,4);
    FriendClass fc;
    fc.showPrivateMembers(objA);
    showPrivate(objA);

    return 0;
}