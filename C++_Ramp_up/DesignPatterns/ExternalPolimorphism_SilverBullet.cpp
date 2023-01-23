#include <iostream>
using namespace std;

class Circle {};
class Square {};
class Triangle {};

class ShapeConcept
{
    public:
        virtual void draw() = 0;
};

template<typename ShapeT, typename DrawerStrategy>
class ShapeModel : public ShapeConcept
{
    public:
        ShapeModel(ShapeT argShape, DrawerStrategy argDrawer) : mShape{move(argShape)}, mDrawer{move(argDrawer)} {}
        void draw() { mDrawer(mShape); }

        ShapeT mShape;
        DrawerStrategy mDrawer;
};


class OpenGLDrawerStrategy
{
    public:
        void operator()(Circle arg) {}
        void operator()(Triangle arg) {}
};

class RotateTriangleStrategy
{
    public:
        void operator()(Triangle arg) {}
};

int main()
{
    ShapeModel<Circle, OpenGLDrawerStrategy> sm(Circle{}, OpenGLDrawerStrategy{});
    ShapeModel<Triangle, RotateTriangleStrategy> sm2 (Triangle{}, RotateTriangleStrategy{});
    sm.draw();
    sm2.draw();

    return 0;
}
