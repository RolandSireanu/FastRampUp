#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

class MyClass
{
    public:

    void setMember(const shared_ptr<MyClass>& arg)
    {
        member = arg;
    }

    ~MyClass()
    {
        std::cout <<"~MyClass() \n"<< std::endl;
    }

    shared_ptr<MyClass> member;
};

int main()
{

    shared_ptr<MyClass> m(new MyClass());
    m->setMember(m);

    return 0;
}