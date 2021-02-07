#include <iostream>
#include <memory>

//Smar pointers : Unique_ptr
//It is a move only data type , can't be copied due to exclusive ownership rule
//When unique_ptr gets out of scope , resource destruction is called , by applying
//delete operator on the raw pointer inside.


//Common application for unique_ptr it is a factory method in a class
//hierarchy . Mostly because it can EASILY convert to shared_ptr


class PU 
{
    public:
    ~PU() { std::cout << "PU destructor !" << std::endl; }
};

class CPU : public PU
{
public:
    CPU(int nrOfCores)
    {
        std::cout << "CPU has " << nrOfCores << " cores " << std::endl;
    }
};

class GPU : public PU
{};

class VPU : public PU
{};


//The three dots stand for a ellipse
//Args = template parameter pack 
//params = function parameter pack
//If ellipse is left of Args , the parameter pack is packed
//If ellipse is right of Args , the parameter pack is unpacked
template<typename T , typename... Args>
std::unique_ptr<T> makeProcessingUnit(Args&&... params)
{
    auto up = std::unique_ptr<T>(nullptr);

    up.reset(new T(std::forward<Args>(params)...));

    return up;
}


int main()
{

    std::shared_ptr<CPU> sGPU = makeProcessingUnit<CPU>(32);

    //================== Construction =============================
    std::unique_ptr<int> up (new int(3));
    //calls deleter for old int , and replace it with the new one
    up.reset(new int(22));    
    //std::unique_ptr<int> up2 = new int(2);        Implicit conv int* -> unique_ptr<int> NOT ALLOWED  !
    
    // template< class T, class... Args >
    // unique_ptr<T> make_unique( Args&&... args );
    
    //============================================================

    // Transfer ownership from up to p , move assigment operator is called
    std::unique_ptr<int> p = std::move(up);     //Move
    std::unique_ptr<int> temp = std::make_unique<int>(0xff);    //Move constructor
    //Return raw pointer 
    std::cout << up.get() << std::endl;


    //Check if up is pointing to a valid object
    if(up == nullptr)
        std::cout <<"nullptr yes indeed ! " << std::endl;
    //Check if up is pointing somewhere
    if(up)
        std::cout << "unique_ptr is pointing to a valid object ! " << std::endl;
    else
        std::cout <<"nullptr yes indeed ! " << std::endl;

    //Return the raw pointer and release the ownership
    //After this call , p should point to nullptr
    std::unique_ptr<int>::pointer ptr = p.release();
    if(!p)
        std::cout << "P is pointing to " << p.get() << std::endl;
    if(p == nullptr)
        std::cout << "P is pointing to nullptr " <<std::endl;
    
    std::cout << "*ptr = " << *ptr << std::endl;

    

    return 0;
}