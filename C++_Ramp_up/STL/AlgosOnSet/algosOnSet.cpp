#include <iostream>
#include <vector>
#include <execution>
#include <random>
#include <string>
#include <utility>
#include <algorithm>
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

vector<size_t> s1 {2,4,5,7,12};
vector<size_t> s2 {1,4,5,10,12};
vector<size_t> result;

int main()
{

    auto it = set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(result));
    printVector(result);
    vector<size_t>().swap(result);

    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(result));
    printVector(result);
    vector<size_t>().swap(result);

    set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(result));
    printVector(result);
    
    vector<size_t> testVector {4,5,12};
    if(includes(s1.begin(), s1.end(), testVector.begin(), testVector.end()))
        print("First vector includes also the second one 1");

    return 0;
}
