#include <iostream>
#include <vector>
#include <execution>
#include <random>
#include <string>
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


vector<size_t> v {2,4,5,5,4};

int main()
{
    print("Vector :");
    printVector(v);
    unsigned int sum = 0;
    
    print("Accumulate (addition) : ", accumulate(v.begin(), v.end(), 0));
    print("Accumulate (multiplication) : ", accumulate(v.begin(), v.end(), 1, multiplies<int>()));
    print("After reduce parallel sum :", reduce(execution::par, v.begin(), v.end()));
    print("Value 5 appears",count(v.begin(), v.end(), 5), "times in vector");
    
    print("===============================================================");
    print("Before :");
    printVector(v);
    transform(v.begin(), v.end(), v.begin(), [](size_t arg){
        return arg * arg;
    });
    print("After transform(v.begin(), v.end(), v.begin(), predicate(n^2)");
    printVector(v);

    print("===============================================================");
    vector<size_t> v3 {1, 1, 1, 1, 1};
    vector<size_t> vResult(v3.size());
    print("First vector : ");
    printVector(v);
    print("Second vector : ");
    printVector(v3);
    transform(v.begin(), v.end(), v3.begin(), vResult.begin(), plus<int>());
    print("After transform(v.begin(), v.end(), v3.begin(), vResult.begin(), plus<int>()):");
    printVector(vResult);

    print("===============================================================");
    vector<size_t> v2 {2, 2, 3, 3, 4};
    print("Dot product of : ");
    printVector(v);
    print(" and ");
    printVector(v2);
    print (" is :", inner_product(v.begin(), v.end(), v2.begin(), 0));
    
    //transform_reduce
    //Apply transform with unary (1 range) or binary operator (over 2 ranges ), apply reduce with binary operator


    print("===============================================================");
    print("Addition and n^2 with transform_reduce");
    printVector(v2);
    print(transform_reduce(std::execution::par, v2.begin(), v2.end(), 0, 
    std::plus<>(),
    [](size_t arg){
        return arg + 1;
    }));

    print("===============================================================");
    //Fist apply transform operation with multiplies<>() , on result, apply reduce operation using plus<>()
    print("Dot product with transform_reduce(v.begin(), v.end(), v2.begin() , 0 , plus<size_t>() ,multiplies<size_t>())");
    print("Dot product = " , transform_reduce(std::execution::par, v.begin(), v.end(), v2.begin() , 0 , plus<size_t>() ,multiplies<size_t>()));
    
    print("===============================================================");
    print("Generating Fibonaci's sequence using adjacent_difference");
    print("Starting from :");
    vector<size_t> v4 {1,2,3,4,5};
    printVector(v4);
    fill_n(vResult.begin(), vResult.size(), 0);
    adjacent_difference(v4.begin(), v4.end(), vResult.begin());
    adjacent_difference(vResult.begin(), prev(vResult.end()), next(vResult.begin()), plus<>{});
    printVector(vResult);

    print("===============================================================");
    print("Extracting 3 random samples from ");
    printVector(v4);
    fill_n(vResult.begin(), vResult.size(), 0);
    sample(v4.begin(), v4.end(), vResult.begin(), 3, std::mt19937{std::random_device{}()});
    printVector(vResult);

    return 0;
}
