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

vector<size_t> v {2,4,4,5,5,7};

int main()
{

    //Searching in unsorted vector 
    auto it = find(v.begin(), v.end() , 5);
    if(it != v.end())
        print("Value ", *it, " found !");
    
    auto r = adjacent_find(v.begin(), v.end());
    print("First pair of adjacent equal elements : ", *r);

    auto r2 = adjacent_find(r+1, v.end(), [](size_t arg1, size_t arg2){ return arg1 == arg2; });
    print("Second pair of adjacent equal elements are : ", *r2);


    //Searching in sorted vector 
    auto bounds = equal_range(v.begin(), v.end(), 5);
    print(*bounds.first, " and ", *bounds.second);

    auto lbound = lower_bound(v.begin(), v.end(), 5);
    print("Lower bound of the subrange that contains values 5 is :", *lbound);

    if(binary_search(v.begin(), v.end(), 7))
        print("Value 7 is part of vector ");

    const vector<size_t> toFind {7,4};
    auto first_match = find_first_of(v.begin(), v.end(), toFind.begin(), toFind.end());
    print("First match is : ", *first_match);

    const vector<size_t> subrangeToFind {4, 4, 5};
    if(search(v.begin(), v.end(), subrangeToFind.begin(), subrangeToFind.end()) != v.end())
        print("Subrange [4, 4, 5] has been found ");

    return 0;
}
