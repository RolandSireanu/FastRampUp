#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>
#include <ranges>

class MyData
{
    public:
        MyData()
        {
        member = 0xC1;
        member1 = 0xC2;
        member2 = 0xC3;
        std::cout << "MyData constructor " << std::endl;
        }

        ~MyData()
        {
        std::cout << "MyData destructor " << std::endl;
        }

        public:
        unsigned int member;
        unsigned int member1;
        unsigned int member2;

        unsigned int getNumber() { return member; }
};


int main()
{
    std::shared_ptr<MyData> sp (new MyData());
    std::shared_ptr<MyData> sp2 (new MyData());
    std::shared_ptr<MyData> sp3 (new MyData());
    std::shared_ptr<MyData> sp4 (new MyData());

    std::cout << sp.use_count() << " , " << sp2.use_count() << " , " << sp3.use_count() << std::endl;
    sp3 = sp2; //sp3 pointer will be deleted and replaced with sp2 pointer
    std::cout << sp.use_count() << " , " << sp2.use_count() << " , " << sp3.use_count() << std::endl;

    sp = nullptr; //sp pointer deleter , replace with nullptr
    std::cout << sp.use_count() << " , " << sp2.use_count() << " , " << sp3.use_count() << std::endl;
    sp4.reset(); //reset() will set the raw pointer of sp4 to nullptr and delete the object

    std::cout << sp.use_count() << " , " << sp2.use_count() << " , " << sp3.use_count() << std::endl;

    //Check whether the managed object is managed only by the current shared_ptr instance
    std::cout << std::boolalpha << sp.unique() << std::endl;
    std::cout << std::boolalpha << sp4.unique() << std::endl;

    if(sp4)
    std::cout <<"sp4 points to valid object != nullptr " << std::endl;
    else
    std::cout <<"sp4 points to nullptr " << std::endl;


    //Exchange the content of two shared_ptr and transfer the ownership without changing
    //the ref counters

    std::shared_ptr<MyData> spA(new MyData());
    spA->member = 0xAA;
    std::shared_ptr<MyData> spB(new MyData());
    spB->member = 0xBB;

    spA.swap(spB);
    std::cout << std::hex << spA->member << std::endl;
    std::cout << "spA.use_count()=" << spA.use_count() << " spB.use_count()=" << spB.use_count() << std::endl;

    //Return stored pointer
    std::cout << std::hex << spA.get() << std::endl;

    return 0;
}