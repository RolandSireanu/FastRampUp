#include <vector>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <string>
#include <cassert>
using namespace std;

int main()
{
    using std::vector;
    
    {
        vector<int> lVec {2, -5, 3, 5, 7};
        auto lIt { std::ranges::find(lVec, 5, [](int arg){ return std::abs(arg);})};
        std::cout << *lIt << "\n";      // Should print -5

        // Print first odd number
        assert((*(std::ranges::find_if(lVec, [](int arg){return std::abs(arg) % 2 == 1;}))) == -5);
        auto lFirst {std::ranges::find_first_of(lVec, vector<int>{-5,3})};
        assert(std::distance(lVec.begin(), lFirst) == 1);
    }

    {
        vector<int> lVec {4,3,2,2,9};
        auto lFirst { std::ranges::adjacent_find(lVec, [](int lhs, int rhs){return lhs < rhs;}) };
        assert(lFirst == lVec.begin() + 3);

        // Search for two consecutive values of 2. Returns a subrange
        assert((std::ranges::search_n(lVec, 2, 2)).begin() == (lVec.begin()+2));

        // Search for subrange {3,2,2} in lVec
        assert(std::ranges::search(lVec, vector<int>{3,2,2}).begin() == lVec.begin()+1);
    }

    {
        vector<int> lVec {5,9,12,18,19};
        // Binary search in a sorted container
        assert(std::ranges::binary_search(lVec, 18) == true);

        // If it were in the container, the value 14 would be on 3rd position
        assert(std::ranges::lower_bound(lVec, 14) == lVec.begin()+3);
        // Maintain a collection sorted with lower_bound
        vector<int> lSortedVec {1,5,8,12};
        int const lValueToAdd {7};
        auto lInsPos {std::ranges::lower_bound(lSortedVec, lValueToAdd)};
        assert(lInsPos == lSortedVec.begin() + 2);
        lSortedVec.insert(lInsPos, lValueToAdd);\
        assert(lSortedVec[2] == lValueToAdd);

        vector<int> lSortedVecDuplicates {1,5,7,7,7,9,12};
        auto lUpperIt {std::ranges::upper_bound(lSortedVecDuplicates, 7)};
        auto lLowerIt {std::ranges::lower_bound(lSortedVecDuplicates, 7)};
        // There are 3 value of 7 in a row
        assert(std::distance(lLowerIt, lUpperIt) == 3);

        // Same operation as above (lower/uppder_bound)
        auto[lDown, lUp] {std::ranges::equal_range(lSortedVecDuplicates, 7)};
        assert(std::distance(lDown, lUp) == 3);

        // Binary search in a partitioned container with respect to value "6"
        vector<int> lVecPartitioned {4, -7, 6, 10, 9, 7};
        assert(std::ranges::binary_search(lVecPartitioned, 6) == true);

    }

    return 0;
}
