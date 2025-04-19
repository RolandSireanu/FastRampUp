#include <vector>
#include <ranges>
#include <algorithm>
#include <iostream>
using namespace std;

namespace SortedVector
{
    template<typename T>
    concept Container = requires(T arg) {
        arg.begin();
        arg.end();
    };
    

    template<Container T>
    void printContainer(const T& arg)
    {
        for(const auto& e : arg)
            std::cout << e << " ";
        std::cout << "\n";
    }

    vector<int> gVec;

    bool InsertInSortedVec(int aValue)
    {
        auto lInsertPoint = ranges::lower_bound(gVec, aValue);
        gVec.insert(lInsertPoint, aValue);

        printContainer(gVec);
        return true;
    }
};


int main()
{
    SortedVector::InsertInSortedVec(23);
    SortedVector::InsertInSortedVec(13);
    SortedVector::InsertInSortedVec(3);
    SortedVector::InsertInSortedVec(99);

    return 0;
}


