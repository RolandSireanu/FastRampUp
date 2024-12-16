#include <ranges>
#include <vector>
#include <iostream>
#include <concepts>
#include <algorithm>

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

// ============================= Defining ranges with santinel =======================
//When the end of a range is defined by an iterator, we need to know where that iterator should point to in advance. 
// That’s not always possible — sometimes our end condition is only uncovered in the process of running the algorithm.
//For example, imagine we wanted our range of numbers to end at the first negative number. 
//We don’t necessarily know where that is in advance, so we can’t provide an iterator to it unless we first run a different algorithm to figure out where that iterator should point to.
//A sentinel is a fairly generic concept within programming. It simply refers to something that can signal an algorithm to end.
//Within the context of C++ ranges, sentinels are objects that can be compared to iterators, using the equality (==) operator. If the operator returns true, that’s the signal for the algorithm to stop.
//A sentinel can be an iterator! But not all sentinels are iterators only


namespace Source
{
    auto generateRandomNumber = [gen = std::mt19937{std::random_device{}()}]() mutable {
        std::uniform_int_distribution<> distr(1, 100); // Define the range [1, 100]
        return distr(gen);
    };

    template<typename T = int>
    vector<T> GetNewVector(int aNrOfElements = 10)
    {
        std::vector<T> v(aNrOfElements);
        std::generate(v.begin(), v.end(), generateRandomNumber);
        return v;
    }
}

namespace Utils
{
    auto onlyEvenPred = [](const int arg){return arg%2==0;};

    template<typename T, typename F>
    class Sentinel
    {
    public:
        bool operator==(T Iter) const{
            return Iter == ContainerEnd || f(*Iter);
        }

        T ContainerEnd;
        F f;
    };

    template<typename T>
    void printContainer(T arg)
    {
        cout << "\n";
        for(const auto& e : arg)
            cout << e << " ";
        cout << "\n";
    }
}

int main()
{
    using std::ranges::for_each;
    using namespace Utils;
    using namespace Source;

    {
        auto lVec {GetNewVector()};
        // It returns a "subrange", subrange is a class that implement view_interface
        auto lSubRange = std::ranges::subrange(lVec.begin(), Sentinel(lVec.end(), [](const int arg){ return arg % 2 == 0 && arg > 50;}));
        printContainer(lSubRange);
    }
 
    {
        // How to find the end of a range?
        // Most of the range-based standard library algorithms return an object that includes an iterator pointing at where the sentinel was triggered
        // For example, the std::ranges::for_each() algorithm returns an object with two fields:
            // in - An iterator to where the sentinel was triggered
            // fun - A reference to the function that we provided to the algorithm
        auto lVec {GetNewVector()};
        auto const [endOfRange, f] = std::ranges::for_each(lVec.begin(), 
                                          Sentinel{lVec.end(), [](const int arg){return arg > 50; }},
                                          [](const int arg){return arg * arg; });
        
        std::ranges::subrange lSub(lVec.begin(), endOfRange);
        cout << "Elements smaller than 50 multipled by themselves :";
        printContainer(lSub);
    }

    {
        auto lVec {GetNewVector()};
        auto localView = lVec | std::views::filter([](const int arg){ return arg%2 == 0;})
                              | std::views::transform([](const int arg){ return arg*arg;})
                              | std::views::reverse;
        printContainer(localView);
    }

    return 0;
}