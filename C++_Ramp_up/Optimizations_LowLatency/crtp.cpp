template<typename T>
class Base
{
    public:
        void f() 
        {             
            cout << "Base::f" << endl; 
            static_cast<T*>(this)->f();
        }
};

class Child : public Base<Child>
{
    public:
        void f() { cout << "Dervied::f" << endl;}
};

template<typename T>
void invoker(T* arg)
{
    Base<T>* b = arg;
    b->f();
}

int main()
{
    Child c;
    invoker(&c);
    return 0;
}