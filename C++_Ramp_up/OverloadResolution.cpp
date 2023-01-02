#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int     addNumbers(int a, int b) { cout << "addNumbers(int,int)" << endl; return a+b; }
float   addNumbers(float a, float b) { cout << "addNumbers(float,float)" << endl; return a + b; }
double  addNumbers(double a, double b) { cout <<"addNumbers(double, double)" << endl; return a+b; }
int     addNumbers(vector<int> a, vector<int> b) { return 0; }

namespace 
{
    int addNumbers(int a, int b) { cout<< "namespace addNumbers(int,int)"<< endl; return a+b;}

    int mathOperation(int a, int b) 
    {
        cout << "namespace mathOperation(int,int)" << endl;
        // ==================================== Overload resolution process: =================================
        // ======== Step_1 Name lookup ======
        // name lookup found the following function declarations and form the list of candidates (overload set):
        // - int addNumbers(int, int)
        // - double addNumbers(double, double)
        // - float addNumbers(float, float)
        // - int addNumbers_internalNamespace(int, int)
        // - int addNumbners(vector<int>, vector<int>)
        
        // ======== Step_2 Removing invalid candidates  ======
        // The compiler needs to remove the invalid candidates based on the following rulles :
        // - Number of arguments
        // - Data type (even with implicit conversion, data type of the passed arguments can't be converted 
        //              to match the declaration even considering implicit conversion)
        // => The new list of candidates (vector<int> got removed because is invalid, 
        //                                there is no implicit conversion from int to vector<int> ):
        // - int addNumbers(int, int)
        // - double addNumbers(double, double)
        // - float addNumbers(float, float)
        // - int addNumbers_internalNamespace(int, int)

        // ======== Step_3 Ranking the remaining(valid) candidates  ======
        // The process of finding a single best match
        // The best match is int addNumbers(int a, int b) from the anonymuous namespace
        return addNumbers(a, b);
    }
};


int main()
{
    cout << mathOperation(5,4);

    return 0;
}
