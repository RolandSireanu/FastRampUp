#include <iostream>
#include <vector>
#include <random>

using namespace std;
vector<size_t> v {5,9,2,1,7,0};


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
    print("Before : ");
    printVector(v);
    print("After std::sort : ");
    sort(v.begin(), v.end());
    printVector(v);

    print("=============================\n");

    shuffleVector(v);
    print("Before : ");
    printVector(v);
    partial_sort(v.begin(), v.begin()+3, v.end());
    print("After std::partial_sort(v.begin(), v.begin()+3, v.end())");
    printVector(v);

    print("=============================\n");
    shuffleVector(v);
    print("Before : ");
    printVector(v);
    nth_element(v.begin(), v.begin()+3, v.end());
    //the nth position is the element that would be in that position in a sorted sequence.
    print("After nth_element(v.begin(), v.begin()+3, v.end())");
    printVector(v);

    print("=============================\n");
    vector<unsigned> testVector_1 {1,2,3,4,5};
    vector<unsigned> testVector_2 {4,5,6,7,8,9,10,18};
    vector<unsigned> finalVector;
    copy(testVector_1.begin(), testVector_1.end(), back_inserter(finalVector));
    copy(testVector_2.begin(), testVector_2.end(), back_inserter(finalVector));
    print("Before : ");
    printVector(finalVector);
    inplace_merge(finalVector.begin(), finalVector.begin()+testVector_1.size(), finalVector.end());
    //Merges two sorted sub arrays into a single one
    print("After inplace_merge(finalVector.begin(), finalVector.begin()+testVector_1.size(), finalVector.end())");
    printVector(finalVector);
    
    

}
