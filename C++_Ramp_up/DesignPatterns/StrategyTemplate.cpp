#include <iostream>
#include <memory>
using namespace std;

// For a good design check if SRP, LSP, OCP, DIP are respected when answer the following two questions
// What happens when you add another type derived from the base class?
// What happens when you add another operation in the base class?

/*
    the Strategy design pattern appears to be strongest in situations where you need to isolate a small number of implementation details. 
    If you encounter a situation where you need to extract the details of many operations, it might be better to consider other approaches (see, for instance, the External Polymorphism design pattern in Chapter 7 or the Type Erasure design pattern
*/


class Circle;
class Square;

template<typename T>
class Drawer
{
    public:
        virtual void draw(const T& arg) = 0;
};

class DrawCircleOpenGL : public Drawer<Circle>
{
    public:
        virtual void draw(const Circle& arg) {}
};
class DrawCircleVulkan : public Drawer<Circle>
{
    public:
        virtual void draw(const Circle& arg) {}
};
class DrawSquareOpenGL : public Drawer<Square>
{
    public:
        virtual void draw(const Square& arg) {}
};
class DrawSquareVulkan : public Drawer<Square>
{
    public:
        virtual void draw(const Square& arg) {}
};


class Shape
{
    public:
        virtual void draw() = 0;
};

class Circle : public Shape
{
    public:
        Circle(unique_ptr<Drawer<Circle>> arg) : drawerStrategy{move(arg)} {}
        void draw() { drawerStrategy->draw(*this); }

        unique_ptr<Drawer<Circle>> drawerStrategy;
};

class Square : public Shape
{
    public:
        //Dependecy injection 
        Square(unique_ptr<Drawer<Square>> arg) : drawerStrategy{move(arg)} {}
        void draw() { drawerStrategy->draw(*this); }

        unique_ptr<Drawer<Square>> drawerStrategy;
};

int main()
{
    unique_ptr<Shape> p {make_unique<Circle>(make_unique<DrawCircleOpenGL>())};
    p->draw();

    return 0;
}
