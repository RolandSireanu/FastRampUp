#include <vector>
#include <variant>
using namespace std;

class Developers
{
public:
    virtual void develop() = 0;
};


class FrontEndDeveloper : public Developers
{
public:
    void develop() final {}
};

class BackendDeveloper : public Developers
{
public:
    void develop() final {}
};

/*
This approach is guaranteed to not allocate separate memory for each developer 
nor use a virtual table. However, in some cases, this approach results in less extensibility, since once the variant is declared, you cannot add another type to it.
*/

template<typename ...Args>
class Project
{
public:
    using Developers = std::vector<std::variant<Args ...>>;

    explicit Project(Developers devs) : _devs(std::move(devs)) {}

    void deliver()
    {
        for(auto& d : _devs)
        {
            std::visit([](auto&& arg){
                arg.develop();
            }, d);
        }
    }

private:
    Developers _devs;

};

int main()
{
    auto bob = FrontEndDeveloper{};
    auto joe = BackendDeveloper{};
    Project<FrontEndDeveloper, BackendDeveloper> p {{bob, joe}};

    return 0;
}