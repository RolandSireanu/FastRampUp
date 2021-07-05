#include <iostream>
#include <ratio>
#include <cstdint>
#include <chrono>
using namespace std;

void print() 
{
    cout << endl;
}

//Variadic templates
template<typename T, typename ...argsT>
void print(const T& arg, const argsT& ...args) 
{
    cout << arg ;
    print(args ...);
}

template<intmax_t n, intmax_t d>
ostream& operator <<(ostream& os , const ratio<n,d> r)
{
    return os << n << " / " << d ;
}

template<typename T>
using my = chrono::duration<double, typename T::period>;

class Base
{
    public:
        void show() {
            cout << "base_show " << endl;
        }

        virtual ~Base() = default;
};

class Derived : public Base {
    public:
    ~Derived() {Base::show();}
};


int main()
{
    print(2.1 , 3.3 , 4.8);

    ratio<3,6> r;
    cout << r << endl;

    print(atto{});
    print(exa{});
    
    using namespace chrono;
    seconds dur {5};
    print(seconds::period{} );
    print(dur.count(), "s");

    microseconds durMs {320};
    print(microseconds::period{});

    durMs += dur;
    print(durMs.count(), " ms");

    dur = dur + duration_cast<seconds>(durMs);
    print(dur.count(), " s");
    
    auto print_seconds = [](const seconds& s) { print(s.count()," s"); };
    print_seconds(100h);
    print_seconds(duration_cast<seconds>(milliseconds{3600}));

    using my_seconds = duration<int, ratio<1,10>>;
    print(my_seconds{1000}.count(), "s");

    //100ms
    using frames = duration<double, ratio<1, 10>>;
    frames frm = frames{seconds(5)};
    cout << frm.count() << endl;

    my<minutes> m = seconds{100};
    m = m + 20000ms;
    cout << m.count() << endl;
    print(m.count(), " m");
    {
        Derived d;
    }
    return 0;
}