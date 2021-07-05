#include <iostream>
#include <vector>
#include <random>

using namespace std;
vector<size_t> v {5,8,2,1,7,0};


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

int main()
{
    auto evenPred = [](size_t arg){
        if(arg % 2 == 0)
            return true;
        else
            return false;
    };

    print("Before :");
    printVector(v);
    partition(v.begin(), v.end(), evenPred);
    print("After partition using even number predicate :");
    printVector(v);

    auto it = partition_point(v.begin(), v.end(), evenPred);
    print("First element which is not part of the partition : ", *it);

    

    return 0;
}
