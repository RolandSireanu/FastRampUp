#include <ranges>
#include <vector>
#include <iostream>
#include <concepts>

// =============================== Ranges in C++2a ============================
// So... what are RANGES ?
//      RANGES are a redefinition of std algorithms coupled with a set of concepts
//      Example: std::sort has been redefined in std::ranges::sort and now with the range concept
//               applied over its template parameter, which makes it accept everything that has a 
//               begin() and end() (this is how the range concept is defined)
// C++20 Ranges, also known as STL v2, effectively replaces existing STL algorithms and facilities.
// Ranges rely on concepts to specify what type of parameters can participate in each overload

// What types does Range accepts as input ?
//  Based on the Range concept, it accepts everything that has a being and end methods
//  Range concept:
//      template< class T >
//      concept range = requires( T& t ) {
//      ranges::begin(t); // equality-preserving for forward iterators
//      ranges::end (t);
//      };

// What is the motivation behinde ranges ?
//  Traditionally for sorting a container you would use the std::sort function
//  with a begin and end iterator pair, but you couldn't do std::sort(container).
//  The old interface is flexible but error prone (mixing two incompatible iterators)
//  Solution:
//      C++2a introduces the notion of RANGES and provide new algorithms that
//      accepts std::ranges. Now std::ranges::sort(v) works if "v" is a range.
//      Vector is a range!

// =========================== Views in C++ =================================
//  Why to use views?
//      Lazy Evaluation: Views provide a mechanism for lazy evaluation, meaning that elements are only processed when they are accessed. This can lead to significant performance improvements, 
//      especially when dealing with large datasets or complex transformations where not all elements need to be processed upfront.
//      Memory Efficiency: Since views do not own the data but instead provide a "window" or "view" into the data, they avoid unnecessary copying or allocation, making operations more memory efficient.
//      Efficient Composition: Views allow you to compose multiple operations (like filtering, transforming, etc.) in a declarative form without creating intermediate containers.
//      Readability and Expressiveness: By using views, you can chain operations in a fluid and expressive way, improving code readability and making the intention of the code more apparent.
//      Separation of Data and Algorithms: Views help separate concerns by allowing algorithms to be applied seamlessly on views without being tied to specific data structures, fostering greater code reusability and flexibility.


template<typename T>
void printContainer(const T& aContainer)
{
    for(const auto& e : aContainer)
        std::cout << e << " ";
    std::cout << std::endl;
}


// =============================== RELATION BETWEEN std::views::xxx and std::ranges::xxx_view ============================================
// ===========================================================================
auto lTransformed = std::views::transform(v, [](int n){return n*n; }) |



std::ranges::transform_view<
    std::ranges::ref_view<
        std::vector<int, std::allocator<int>> 
    >, 
    __lambda_52_50
> lTransformed = std::ranges::views::transform.operator()(v, __lambda_52_50);
// ============================================================================

// ==============================================================================
auto lTransformed = std::views::transform(v, [](int n){return n*n; }) |
                    rv::filter([](const int& value){return value % 2 == 0; });

std::ranges::filter_view<
    std::ranges::transform_view<
        std::ranges::ref_view<std::vector<int, std::allocator<int> > 
        >, __lambda_52_50
    >, 
    __lambda_53_23
> lTransformed = operator|(std::ranges::views::transform.operator()(v, __lambda_52_50), static_cast<const std::ranges::views::__adaptor::_RangeAdaptor<std::ranges::views::_Filter>&>(std::ranges::views::filter).operator()(__lambda_53_23));
// ==============================================================================
// =============================== RELATION BETWEEN std::views::xxx and std::ranges::xxx_view ============================================


int main()
{
    std::vector<int> v{7,3,1,0,12,55,12};
    std::ranges::sort(v);
    printContainer(v);

    std::ranges::find(v.begin(), std::unreachable_sentinel, 55);
    std::ranges::find(v,55);


    return 0;
}