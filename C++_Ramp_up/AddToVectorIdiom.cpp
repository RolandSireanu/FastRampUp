#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Employee
{
    Employee(const string& arg_name, int arg_age) : name{arg_name}, age{age} { cout << "Arguments constructor !" << endl; }
    Employee() { cout << "Default ctor \n"; }
    Employee(const Employee&) { cout << "Copy ctor \n"; }
    Employee(Employee&&) { cout << "Move ctor \n"; }

    string name = "Default_name";
    int age = 18;
    unsigned int data[512] {0};
};


class Employees
{
    public:
        template<typename ...Args>
        void add(Args ...args)
        {
            v.emplace_back(forward<Args>(args)...);
        }

    private:
        vector<Employee> v;
};



int main()
{
    Employees e;
    e.add("Roland", 23);


    return 0;
}
