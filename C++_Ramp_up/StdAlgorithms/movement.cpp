#include <vector>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <string>
#include <cassert>
using namespace std;

template<typename T>
void printContainer(const T& aContainer)
{
    for(auto const& e : aContainer)
        cout << e << " ";
    cout << "\n";
}

int main()
{
    using std::vector;
    
    {
        vector<int> lVec {2, -5, 3, 5, 7};
        vector<int> lDest (5);
        std::ranges::move(lVec, lDest.begin());
        assert(lDest[1] == -5);
        assert(lDest[4] == 7);
    }

    {
        vector<int> lVec {2, -5, 3, 5, 7};
        vector<int> lDest (5);
        std::ranges::move_backward(lVec, lDest.end());
        assert(lDest[1] == -5);
        assert(lDest[4] == 7);
    }

    {
        vector lVec{"A", "B", "C", "D"};
        std::ranges::rotate(lVec, lVec.begin()+1);
        printContainer(lVec);
    }

    return 0;
}
