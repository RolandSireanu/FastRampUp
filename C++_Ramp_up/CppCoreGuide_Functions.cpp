#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <span>
using namespace std;

namespace
{
    void example()
    {
        vector<int> v {4,9,1,2,0,2,99,83};

        // BAD: sort(v.begin(), v.end(), [](int a, int b){
        // Naming that lambda breaks up the expression 
        // into its logical parts and provides a strong hint to the meaning of the lambda.
        auto greaterThan = [] (int a, int b) { return a > b; };
        sort(v.begin(), v.end(), greaterThan);

        for(auto val : v)
        {
            std::cout << val << endl;
        }
    }


    class Computer
    {
        public:
            //If a function is short and simple you can inline it
            //Mark it noexcept and const if it is the case 
            //Declaring a function noexcept helps optimizers:
            //  - by reducing the number of alternative execution paths
            //  - not generating the setup for stack unwinding 
            //  - speed up the stl operations by moving (if you moves are noexcept)
            // Destructors, swap functions, move operations, and default constructors should never throw.
            inline int ram() const noexcept 
            { 
                return mRamSize; 
            }

        private:
            int mRamSize;
    };

    // For general use, take T* or T& arguments rather than smart pointers
    // Passing a smart pointer transfers or shares ownership and should only be used when ownership semantics are intended. 
    // A function that does not manipulate lifetime should take raw pointers or references instead.
    // Passing by smart pointer restricts the use of a function to callers that use smart pointers
    // There is no reasson to use: unique_ptr<Computer> or shared_ptr<Computer> because there is no lifetime management
    void infoAboutComputer(Computer* aComputer)
    {
        cout << aComputer->ram() << endl;
    }

    // For small data types use passing by value to avoid the access overhead of a const ref&
    // Check OneNote Articole for additional details
    void f(const int&) {}
    void f(int argument){}

    // Prefare default arguments to overloads
    //The use of default arguments can avoid code replication.
    // BAD
        void print(const string& s);  // use default format
        void print(const string& s, format f);
    //GOOD
        void print(const string& s, format f = {});


    // =============================== Return value ==================================================

    //A return value is self-documenting, whereas a & could be either in-out or out-only and is liable to be misused.
    //If you have multiple return values use a tuple of similar
    vector<const int*> find_all(const vector<int>&, int x);

    //Don't use const for return type, it interferes with move sematics
    // const vector<int> compute();
    vector<int> compute();

    //Don't return T&&, it is a magnet for rvalues whose lifetime ends at the end of the function
    // template<typename T>
    // T&& f();



}   

int main()
{
    example();
}
