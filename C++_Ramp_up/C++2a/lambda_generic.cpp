struct Laptop
{
    int id;
    double price;
};


// Using "auto" int lambda declaration
auto lambda1 = [](const auto& lhs, const auto& rhs) { return true; };
// =======> Translates to 
// template<>
// inline /*constexpr */ bool operator()<int, Laptop>(const int & lhs, const Laptop & rhs) const
// {
// return true;
// }


// Using "typename" definition in lambda declaration
auto lambda2 = []<typename T>(T lhs, T rhs) { return lhs > rhs; };




// template<typename T1, typename T2>
// concept Comparable = requires(T1 a, T2 b) {
//     { a < b } -> std::convertible_to<bool>;
// };

using HighToLowCmp = decltype([]<typename T>(const T& lhs, const T& rhs){ return lhs > rhs; });

template<typename K, typename V>
using MapSortedHighToLow = std::map<K,
                                    V,
                                    HighToLowCmp
                                    >;


// ======================= Parameter pack in lambda =======================
template<typename ...T>
void f(T&& ...args)
{
    auto lambda = [ ... _args = std::forward<T>(args)]<typename ...Ts>(Ts&& ... args)
    {
        
    };
}