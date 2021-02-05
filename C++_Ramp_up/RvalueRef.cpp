#include <iostream>
#include <cstring>
#include <vector>

void* operator new[](size_t arg)
{
    std::cout << "Memory allocation size = " << arg << std::endl;
    return malloc(arg);
}


void operator delete[](void* ptr)
{
    std::cout << "Memory dealocatin " << std::endl;
    free(ptr);
}

//Rvalue references 
// Rvalue references remove the overhead of copying the temporal objects 


//Rule of 3 just changed to rule of 5 by adding the rvalue copy constructor and rvalue = operator
class Buffer
{
    public:
        Buffer(const size_t arg): dataBuffer(new unsigned char[arg])
        {
            std::cout << "Buffer constructor simple ! " << std::endl; 
            size = arg;
        }

        ~Buffer() 
        {
            std::cout << "Buffer destructor ! " << std::endl; 
            delete[] dataBuffer; 
        }

        //Copy constructor 
        Buffer(const Buffer& arg) 
        {
            this->size = arg.size;
            delete this->dataBuffer;
            this->dataBuffer = new unsigned char[arg.size];            
            memcpy(this->dataBuffer , arg.dataBuffer, arg.size);            
        }

        Buffer(Buffer&& arg)
        {
            this->size = arg.size;
            this->dataBuffer = arg.dataBuffer;
            arg.dataBuffer = nullptr;
        }

        //Copy assigment operator
        Buffer& operator=(const Buffer& arg)
        {
            std::cout << "Copy assigment operator , const ref ! " << std::endl;
            this->size = arg.size;
            delete this->dataBuffer;
            this->dataBuffer = new unsigned char[arg.size];            
            memcpy(this->dataBuffer , arg.dataBuffer, arg.size);            

            return *this;
        }


        Buffer& operator=(Buffer&& arg)
        {

            std::cout << "Copy assigment operator , rvalue ! " << std::endl;
            this->size = arg.size;
            delete this->dataBuffer;
            this->dataBuffer = arg.dataBuffer;
            arg.dataBuffer = nullptr;

            return *this;


        }


    private:
    size_t size;
    unsigned char* dataBuffer;
};


//No memory allocation is done here ! 
//Just reasource stealing
template<typename T>
void f(T&& arg)
{
    static std::vector<T> v;
    v.emplace_back(std::forward<T>(arg));    
}



int main()
{

    Buffer b(100);    

    //No memory allocation is done here ! 
    //The conversion to rvalue will result in linking the generic reference function argument
    f(std::move(b));
    
    return 0;
}