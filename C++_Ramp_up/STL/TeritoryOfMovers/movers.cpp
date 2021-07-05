#include <iostream>
#include <vector>
#include <execution>
#include <random>
#include <chrono>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;
using namespace std::chrono;

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

using vec = vector<size_t>;
vector<vec> matrix1;
vector<vec> matrix2;
vector<vec> result;

size_t measure(function<void(void)> f_arg)
{
    auto start = high_resolution_clock::now();
    // copy(matrix1.begin(), matrix1.end(), back_inserter(result));
    f_arg();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count();
}

int main()
{
    print("Generating 1000x1000 matrix ... ");
    generate_n(back_inserter(matrix1), 1000, []() { return vec(1000,0xAA); });
    generate_n(back_inserter(matrix2), 1000, []() { return vec(1000,0xBB); });

    size_t time = measure([](){ copy(matrix1.begin(), matrix1.end(), back_inserter(result)); });
    print("Copy matrix to destination using copy(begin, end, output) :",time, "us");

    time = measure([](){ move(matrix1.begin(), matrix1.end(), back_inserter(result)); });
    print("Moving same matrix to destination using move(begin, end , output) :", time, "us");

    print("Swap ranges ... ")
    print(measure([](){ swap_ranges(matrix2.begin(), matrix2.end(), result.begin()); } ));
    

    return 0;
}
