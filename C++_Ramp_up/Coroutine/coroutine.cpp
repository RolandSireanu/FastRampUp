#include <experimental/coroutine>
#include <iostream>
using namespace std;

Generator<string> produce()
{
    string temp = "abcdefghij";
    unsigned int counter=0;

    while(true)
    {
        co_yield temp[counter];
        counter++;
    }
}

int main()
{

    for(const auto& e : produce())
    {
        std::cout << e << std::endl;
    }
}