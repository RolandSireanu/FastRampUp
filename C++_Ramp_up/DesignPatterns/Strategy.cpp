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

class DrawCircleStrategy
{
    public:
        virtual void draw(const Circle& arg) = 0;
};
class DrawSquareStrategy
{
    public:
        virtual void draw(const Square& arg) = 0;
};

class DrawCircleOpenGL : public DrawCircleStrategy
{
    public:
        void draw(const Circle& arg) { /* OpenGL implementation*/}
};
class DrawCircleVulkan : public DrawCircleStrategy
{
    public:
        void draw(const Circle& arg) { /* Vulkan implementation */}
};

class DrawSquareOpenGL : public DrawSquareStrategy
{
    public:
        void draw(const Square& arg) { /* OpenGL implementation */}
};
class DrawSquareVulkan : public DrawSquareStrategy
{
    public:
        void draw(const Square& arg) { /* Vulkan implementation */}
};


class Shape
{
    public:
        virtual void draw() = 0;
};

class Circle : public Shape
{
    public:
        Circle(unique_ptr<DrawCircleStrategy> arg) : drawerStrategy{move(arg)} {}
        void draw() { drawerStrategy->draw(*this); }

        unique_ptr<DrawCircleStrategy> drawerStrategy;
};

class Square : public Shape
{
    public:
        //Dependecy injection 
        Square(unique_ptr<DrawSquareStrategy> arg) : drawerStrategy{move(arg)} {}
        void draw() { drawerStrategy->draw(*this); }

        unique_ptr<DrawSquareStrategy> drawerStrategy;
};

int main()
{
    unique_ptr<Shape> p {make_unique<Circle>(make_unique<DrawCircleOpenGL>())};
    p->draw();

    return 0;
}
