    #include <iostream>
    #include <cstring>
    #include <string>
    #include <vector>
    using namespace std;
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

    void fnct(const string&)
    {
        // cout << arg << endl;
    }

    //This is not an rvalue reference, because the element
    //in front is a template argument , this construction is
    //called UNIVERSAL REFERENCE
    // if arg is an rvalue => the argument will become rvalue refence
    //if arg is an lvalue => lvalue reference
    template<typename T>
    const char* type_label(T&& arg) {
        return std::is_rvalue_reference<decltype(arg)>::value ? "rvalue" : "lvalue";
    }

    //std::forward  , is just a conditional mode 
    //if arg is an rvalue refence will apply the std::move(arg)
    //if arg is an lvalue refenrece will forward as it is without
    //any conversion 
    template<typename T>
    void print_type(T&& arg) {
        //Why we need std::forward ? 

        //print_type(5) => type of arg will be an int&& arg , an rvalue ref
        // BUT arg , is an lvalue (este la stanga expresiei)
        // An rvalue refence it is ALWAYS and LVALUE 
        cout << type_label(std::forward<T>(arg)) << endl;
    }


    // When not to use rvalue references 
    // RVO (Return value optimization) , compiler will automatically 
    // move the resource , or will build the string in the calling function (even better than move)
    // No return move(a) or string&& make_string() is required here
    // Let the compiler handle the return value for you !
    string make_string() {
        string s;

        return s;
    }

    Buffer getBuffer() 
    {
        Buffer tempA;
        Buffer tempB;

        if(true)
            return tempA;
        else
            return tempB;
    }

    int main()
    {

        Buffer b(100);    
        
        //COnst reference can bind on rvalue as opposed to non-const references
        //This behaviour is accepted because you will want to call the 
        //fnct function like this : "something" with an rvalue
        fnct("baba");

        

        //No memory allocation is done here ! 
        //The conversion to rvalue will result in linking the generic reference function argument
        f(std::move(b));
        
        int x = 0;
        int* px = &x;
        int*& rpx = px;

        cout << "px = " << px << " &px = " << &px << endl;
        cout << "rpx = " << rpx << " &rpx = " << &rpx << endl;

        // cout << type_label('a') << endl;
        // cout << type_label(x) << endl;
        // cout << type_label(std::move(x)) << endl;
        print_type(999);

        //Does the temp reference a deallocated memory?
        // No, getBuffer receives memory from current stack(stack of main) to build the result there
        // The "temp" reference just reference that memory location => All good
        Buffer const& temp = getBuffer();

        return 0;
    }