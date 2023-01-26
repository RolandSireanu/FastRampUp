#include <iostream>
using namespace std;

// Bridge design pattern
// It links two abstractions, in this case, Operating system and GUI.
// For each Os there is a specific GUI to be used, when an Os class is instantiated
// the corresponding Gui is automatically instantiated in the pimpl pointer.

class Button{}; class WindowsButton:public Button{};  class UnixButton:public Button{}; 

class Gui
{
    public:
        virtual Button* createButton() = 0;
};
class WindowsGui : public Gui
{
    public:
        Button* createButton() override { cout <<" WindowsButton" << endl; return new WindowsButton{}; }
};
class UnixGui : public Gui
{
    public:
        Button* createButton() override { return new UnixButton{}; }
};


class Os
{
    public:
        virtual void createInterface() = 0;
    protected:
        Os(Gui* arg) : pimpl{arg} {}

        Gui* getGui() { return pimpl; }
        Gui const* getGui() const { return pimpl; }
    private:
        Gui* pimpl;
};
class Windows : public Os
{
    public:
        Windows(): Os{new WindowsGui{}} {}
        void createInterface() override { getGui()->createButton(); }
};
class Linux : public Os
{
    public:
        Linux() : Os{new UnixGui{}} {}
        void createInterface() override { getGui()->createButton(); }
};




int main()
{
    Os* osPtr { new Windows{}};
    osPtr->createInterface();

    return 0;
}
