#include <iostream>
#include <type_traits>
#include <string>
using namespace std;

template <typename T , unsigned lines, unsigned cols>
class Matrix {

};

template<typename T, int size>
using MyVector = Matrix<T, 1, size>;
using Strange = Matrix<double, 1, 1>;

template <typename T>
class Array {

    public:
        Array() = default;

        template<typename T2>
        Array<T>& operator = (Array<T2>& )
        {
            static_assert(is_convertible<T2,T>::value, "Cannot convert from one type to another ! ");
            cout << "Copy asigment operator ! " << endl;
            return *this;
        }
};


int main()
{
    Strange s;
    MyVector<double, 10> v;

    Array<double> ad;
    Array<float> ai;
    ad = ai;
}