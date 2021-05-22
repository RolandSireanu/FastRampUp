#include <iostream>
#include <string>
#include <vector>
using namespace std;


// 3 Cases in which you shouldn't use const 

class MyClass {
    
    public:

    //If you declare non static members as const , copy and move operation will not be 
    //used implictilly anymore , it is recomended to avoid this situation
    const int SIZE  = 3;
};

//By declaring the return type as const , it is possible to disable the RVO
const string getText()
{
    return "Hello world";
}


//Don't declare const types passed in stl templates 
// vector<const int> v;

int main()
{
    return 0;
}