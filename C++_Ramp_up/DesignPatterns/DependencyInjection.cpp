#include <iostream>
#include <string>
using namespace std;

//Reduce coupling between Project and Front/BackendDeveloper class using Dependency injection
//What is dependency injection? Passing pointer to dependecy in constructor

enum class Status
{
    SUCCESS = 1,
    FAIL = 2
};

class Developer
{
    public:
        Developer() = default;
        virtual Status develop() const = 0;
};

class FrontDeveloper : public Developer
{
    public:
        FrontDeveloper(int id, string name) {}
        FrontDeveloper(float salary) {}
        Status develop() const final { return Status::SUCCESS;}
};
class BackendDeveloper : public Developer
{
    public:
        BackendDeveloper(int id, string name) {}
        Status develop() const final { return Status::SUCCESS;}
};

class Project
{
    public:
        Project(Developer* d) : mDev{d} {}
    private:
        Developer* mDev;
};


int main()
{
    FrontDeveloper* frontDev = new FrontDeveloper(453.21f);
    Project p{frontDev};

    return 0;
}
