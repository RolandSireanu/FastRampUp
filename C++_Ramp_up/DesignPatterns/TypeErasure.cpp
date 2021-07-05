#include <iostream>
#include <memory>
#include <utility>
#include <vector>
using namespace std;

namespace 
{
    const double PI = 3.1455;
};

class square final 
{
    public:
        explicit square(const double side) : side{side} {}
        double perimeter() const { return 4 * side; }
        double area() const { return side*side; }
    private:
        double side = 0;

};

class circle final 
{
    public:
        explicit circle(const double radius) : radius{radius} {}
        double perimeter() const { return 2 * PI * radius; }
        double area() const { return PI*radius*radius; }
    private:
        double radius = 0;
};

void draw(const square& arg_square) { cout <<"Drawing square \n"; }
void draw(const circle& arg_square) { cout <<"Drawing circle \n"; }

class shape final
{
    public:

        template<typename T>
        shape(T&& arg_impl) : impl{make_unique<wrapper<T> >(move(arg_impl))} {}
        shape(const shape& arg) : impl{ arg.impl->clone() } { }
        double perimeter() const { return impl->perimeter(); }
        double area() const { return impl->area(); }
        void draw() const { impl->draw(); }

    private:
        class base
        {
            public:
                virtual ~base() = default;
                virtual double perimeter() const = 0;
                virtual double area() const = 0;
                virtual void draw() const = 0;
                virtual unique_ptr<base> clone() const = 0;
        };

        template<typename T>
        class wrapper final : public base 
        {
            public:
                wrapper(T&& object): object{move(object)} {}
                double perimeter() const final { return object.perimeter(); }
                double area() const final { return object.area(); }
                void draw() const final { return ::draw(object); }

                unique_ptr<base> clone() const
                {
                    return make_unique<wrapper>(*this);
                }

            private:
                T object;
        };   

        unique_ptr<base> impl;

};

int main()
{
    shape s{circle{5}};
    vector<shape> v { square{4}, circle{10} };
    for (const shape& s : v)
        cout << s.area() << endl;

    for(const auto& s : v)
        s.draw();

    return 0;
}
