#include <iostream>
#include <vector>
#include <execution>
#include <random>
#include <string>
#include <utility>
using namespace std;

namespace
{
    template<typename T>
    void printVector(const vector<T>& v)
    {
        for(const auto& e : v)
            cout << e << " ";
        cout <<endl;
    }  

    template<typename T>
    void shuffleVector(vector<T>& v)
    {
        auto rng = std::default_random_engine {};
        shuffle(std::begin(v), std::end(v), rng);
    } 

    void print()
    {
        cout << endl;
    }

    template<typename T, typename ...Args>
    void print(T arg, Args... args)
    {
        cout << arg << " ";
        print(args...);
    }


};

vector<size_t> v {2,4,2,5,4};

int main()
{

    print("=================== Querry a property in 1 range ==================");
    bool result = all_of(execution::par, v.begin(), v.end(), [](size_t arg){
        return arg % 2 == 0 ? true : false;
    });
    if(result)
        print("All elements are even");
    else
        print("Not all element are even");


    result = any_of(execution::par, v.begin(), v.end(), [](size_t arg){
        return arg % 2 == 0 ? true : false;
    });
    if(result)
        print("At least one element is even ");
    else
        print("None of the elements are even");

    result = none_of(execution::par, v.begin(), v.end(), [](size_t arg){
        return arg > 5 ? true : false;
    });
    if(result)
        print("None of the elements are bigger than 5");
    else
        print("At least an element is bigger than 5");

    
    print("====================== Querry a property in 2 ranges ====================");
    print("Check palindrom with std::equal");
    string objectName {"MAAAM"};
    if(equal(objectName.begin(), objectName.begin() + objectName.size()/2, objectName.rbegin()))
        print("Object name is palindrom");
    else
        print("Object name is not palindrom");


    string s1 {"Ionescu"};
    string s2 {"Ionila"};
    //first range < second range
    bool r = lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
    if(r)
    {
        print(s1);
        print(s2);
    }
    else
    {
        print(s2);
        print(s1);
    }

    print("Check mismatch between ",s1," and ",s2);
    auto p = mismatch(s1.begin(), s1.end(), s2.begin());
    print("First mismatch ch s1 : ", *(p.first));
    print("First mismatch ch s2 : ", *(p.second));


    return 0;
}
