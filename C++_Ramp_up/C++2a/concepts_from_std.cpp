#include <string>
#include <iostream>
#include<memory>
#include <type_traits>
#include <vector>
#include <concepts>
#include <array>
using namespace std;


// ============================ C++ concepts defined in stl for functions/classes ====================

template <typename T>
requires convertible_to<T,bool>
void printBool(T aArg) { std::cout << std::boolalpha << aArg << std::endl; }

// ------------------------------------------------------------------------------
#define COMPARABLE_VERSION

struct Comparable
{
    auto operator<=>(const Comparable& rhs) const = default;
    int member;
};

struct NonComparable 
{
    int member;
};

template<typename T>
requires std::totally_ordered<T>
bool compare(T a, T b) { return a == b; }

// =========================== C++ concepts defined in stl for iterators =============
#include <iterator>

template<typename F, typename IT>
requires std::indirect_unary_predicate<F, IT>
bool is_true(F aCallable, IT aIterator)
{
    return aCallable(*aIterator);
}

template<typename F, typename ITLHS, typename ITRHS>
requires std::indirectly_comparable<ITLHS, ITRHS, F>
bool are_equal(F aCallable, ITLHS aItLhs, ITRHS aItRhs)
{
    return aCallable(*aItLhs, *aItRhs);
}


int main()
{
    printBool(true);

    // ----------------------------------------------------------
    #ifdef COMPARABLE_VERSION
        printBool(compare(Comparable{1}, Comparable{1}));
    #else
        printBool(compare(NonComparable{1}, NonComparable{1}));
    #endif
    // ----------------------------------------------------------

    std::vector<int>     lContainer1 {1,2,3,4};
    std::array<int, 4>   lContainer2  {0,1,2,3};



    std::cout << std::boolalpha << are_equal([](int a, int b) -> bool {
        return a == b;
    }, lContainer1.begin(), lContainer2.begin()) << "\n";



    return 0;
}