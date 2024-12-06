#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>
using namespace std;
//Weak_ptr is a smart_pointer that holds a non-owning reference to an object which is managed by a
//shared_ptr. It must be converted to shared_ptr in order to access the object's data

class Widget
{

public:
unsigned int member = 0xff;

    ~Widget()
    {
        std::cout << "Widget destructor ! " << std::endl;
    }
};


//Slow function , maybe a read from database or file
unique_ptr<Widget> readWidget(int id)
{
    unique_ptr<Widget> temp(new Widget());

    return temp;
}


//All the reads are cached in unordered_map
//Weak_ptr used for checking the referenced object lifetime , if has expired
//no other shared_ptr points to it , read a new instance otherwise , return an used one
shared_ptr<const Widget> readFastWidget(int id)
{
    static std::unordered_map<int,weak_ptr<const Widget>> cache;

    shared_ptr<const Widget> ret = cache[id].lock();

    if(ret == nullptr)
    {
    ret = readWidget(id);
    cache[id] = ret;
    }

    return ret;
}

int main()
{

    shared_ptr<Widget> a(new Widget());
    shared_ptr<Widget> b(new Widget());
    shared_ptr<Widget> c(new Widget());

    a=b;
    b=a;
    std::cout << a.use_count() << " , " << b.use_count() << " , " <<c.use_count() << std::endl;


    return 0;
}