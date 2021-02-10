#include <iostream>
#include <vector>
#include <memory>
#include <string>

// void* operator new(size_t arg)
// {
//     std::cout << "Memory allocation size = " << arg << std::endl;
//     return malloc(arg);
// }


// void operator delete[](void* ptr)
// {
//     std::cout << "Memory dealocatin []" << std::endl;
//     free(ptr);
// }

// void operator delete(void* ptr)
// {
//     std::cout << "Memory dealocatin " << std::endl;
//     free(ptr);
// }

// Shared_ptr
//Downsides : 
    // Twice as big as raw pointer , internally contain raw pointer to resource and raw pointer to 
    // control block (reference counter)

    //Memory for the control block has to be dynamically allocated. 
    //When make_shared can be used , this cost of allocation is eliminated because make_shared 
    //make 1 allocation for data and control block

    //Reference count is atomic , and atomic operations are always slower 

//Even with custom deleter  and allocator , a shared_ptr is constant in size , because
//pointer to deleter and allocator are stored in control block together with reference count and weak count

//Using custom deleter is not possible with make_shared
//Don't pass raw pointers to shared_ptr , if there are other shared_ptr pointing to the same raw pointer
//this will result in undefined behaviour
using namespace std;

class Arrow
{

    public:
    Arrow(std::string arg) : direction(arg) { std::cout <<"Arrow constructor ! " << std::endl;}
    ~Arrow() { std::cout <<"Arrow destructor ! " << std::endl; }

    void resetArrow()
    {
        direction = "none";
    }

    std::string direction = "none";
};


class Pool : public std::enable_shared_from_this<Pool>
{

    class Deleter
    {
        public:
        Deleter(weak_ptr<Pool> wp) : pool(wp) {}

        void operator()(Arrow* arg)
        {   
            if(!pool.expired())
            {

                std::cout << "Reset arrow and return it in the pool ! \n";
                arg->resetArrow();                     
                pool.lock()->addToPool(arg);        
            }
            else
            {
                delete arg;
            }
        }

        private:
            weak_ptr<Pool> pool;
    };

    public:
        Pool(unsigned int poolSize)
        {

        }

        void addToPool(Arrow* argArrow)
        {                     
            arrows.push_back(argArrow);
        }

        shared_ptr<Arrow> acquire()
        {            
            if(arrows.size() > 0)
            {                
                Arrow* raw = arrows.back();                
                arrows.pop_back();
                shared_ptr<Arrow> ret (raw,Pool::Deleter(shared_from_this()));

                std::cout << "There are arrows in vector ! " << std::endl;
                return ret;             

            }
            else
            {
                std::cout << "Instantiate a new Arrow ! " << std::endl;                
                shared_ptr<Arrow> temp(new Arrow("left"), Pool::Deleter(weak_ptr<Pool>(shared_from_this())));                                
                return temp;
            }
            
        }

        ~Pool()
        {
            for(auto a : arrows)
            {
                delete a;
            }
        }

    private:

        vector<Arrow*> arrows;
    
};


int main()
{

    shared_ptr<Pool> p = make_shared<Pool>(2);
    {
        shared_ptr<Arrow> ar = p->acquire();
        shared_ptr<Arrow> ar2 = p->acquire();
        shared_ptr<Arrow> ar3 = p->acquire();
    }

    shared_ptr<Arrow> ar = p->acquire();
    shared_ptr<Arrow> ar2 = p->acquire();
    shared_ptr<Arrow> ar3 = p->acquire();


    std::cout<<"Program finish ! " << std::endl;
    return 0;
}