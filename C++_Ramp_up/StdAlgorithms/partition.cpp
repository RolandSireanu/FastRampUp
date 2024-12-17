#include <vector>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <string>
using namespace std;

class Object
{
    
    public:
    Object() { cout << "Default constructor " << endl; }
    Object(const Object&) { cout << "Copy constructor " << endl; }
    Object(const Object&&) { cout << "Move constructor " << endl; }
    Object& operator=(const Object&) { cout << "Copy asigment operator" << endl; }
    Object& operator=(const Object&&) { cout << "Move asigment operator" << endl; }
    operator bool() { cout << "Bool operator "<<endl; return true; }
    Object(int a) : member{a} { cout << "Converting constructor 1 int" << endl; }
    Object(int a, int b, int c) { cout << "Converting constructor 3 int args" << endl; }
    Object(std::initializer_list<int> arg) { cout <<"Constructor initializer_list " << endl; }
    int member;
};

template<typename T>
void printContainer(T arg)
{
    for(const auto& e : arg)
        cout << e << " ";
    cout << "\n";
}

enum class PartType{
    PARTITION,
    STABLE_PARTITION
};


template<PartType P>
void partitionTest(vector<int>&& v)
{
    using std::vector;

    auto performPartitioning = [&v](auto partFunction){
        auto subRange = partFunction(v, [](int x){return x < 0; });
        std::ranges::subrange firstSubRange{v.begin(), subRange.begin()};
        printContainer(firstSubRange);
        printContainer(subRange);   
    };

    if constexpr(P == PartType::PARTITION)
    {
        performPartitioning(std::ranges::partition);
    }
    else if constexpr(P == PartType::STABLE_PARTITION)
    {
        performPartitioning(std::ranges::stable_partition);
    }
}


int main()
{
    using std::vector;
    partitionTest<PartType::PARTITION>(vector<int>{-3,2,1,19,20,-4,5,-87});
    partitionTest<PartType::STABLE_PARTITION>(vector<int>{-3,2,1,19,20,-4,5,-87});


    return 0;
}
