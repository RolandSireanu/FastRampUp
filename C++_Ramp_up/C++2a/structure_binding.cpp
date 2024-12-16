#include <tuple>
#include <string>
#include <iostream>
using namespace std;

struct Person
{
    int id;
    string name;
};

std::tuple<int, string> CreatePerson()
{
    return {1 , "John"};

}

int main()
{

    // Create structure binding from tuple
    auto [var1, var2] = std::make_tuple(1,2);
    auto[var3, var4] = CreatePerson();
    auto const[var5, var6] = CreatePerson();
    // auto const&[var7, var8] = CreatePerson(); It is also possible, doesn't make sense in current scenario

    // Create structure binding from struct
    auto [var9, var10] = Person{10, "Doe"};

    //Create structure binding from pair
    auto [var11, var12] = std::make_pair(5, "Alexander");

    // You can unpack arrays into structure binding
    int myArray[3] {9,8,7};
    auto [v1, v2 ,v3] =  myArray;

    // Values can be ignored
    auto[v4, _, v6] = myArray;

    return 0;
}