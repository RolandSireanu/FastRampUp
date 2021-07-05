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
    print("Before :");
    printVector(v);
    rotate(v.begin(), v.begin()+2, v.end());    
    print("After rotate(v.begin(), v.begin()+2, v.end())");
    printVector(v);

    print("Before :");
    printVector(v);
    reverse(v.begin(), v.end());
    print("After reverse(v.begin(), v.end())");
    printVector(v);

    print("Before :");
    printVector(v);
    next_permutation(v.begin(), v.end());
    print("After next_permulation(v.begin(), v.end())");
    printVector(v);


    print("Before :");
    printVector(v);
    random_shuffle(v.begin(), v.end());
    print("Before : random_shuffle(v.begin(), v.end())");
    printVector(v);

    return 0;
}
