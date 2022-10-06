#include <iostream>
using namespace std;

// METAFUNCTIONS
// Metafunctions are a classes, structs or in some cases even aliases

//Metafunction that "returns a value "
template<int a, int b>
struct sum
{
    static constexpr int value = a + b;
};

//Metafunction that "returns a type" 
template<typename T>
struct echo_type
{
    using type = T;
};
template<typename T>
using echo_type_t = typename echo_type<T>::type;



//Very useful metafunction
template<class T, T v>
struct my_integral_constant
{
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant<T, v>;

    constexpr operator value_type() const noexcept  { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

//Just some helpful templates for future implementations
template<bool v>
using my_bool_constant = my_integral_constant<bool, v>;
using my_true_type = my_bool_constant<true>;
using my_false_type = my_bool_constant<false>;
template<typename T>
struct my_is_void : my_false_type {};
template<>
struct my_is_void<void> : my_true_type {};


// Metafunction for removing const from type
template<typename T>
struct my_type_identity
{
    using type = T;
};
template<typename T>
using my_type_identity_t = my_type_identity<T>::type;

template<typename T>
struct my_remove_const : my_type_identity<T> {};

template<typename T>
struct my_remove_const<T const> : my_type_identity<T> {};

template<typename T>
using my_remove_const_t = my_remove_const<T>::type;


// Conditional metafunction, returns a type or another, 
// depending on the condition evaluation
template<bool cond, typename T, typename F>
struct my_condition : my_type_identity<T> {};

template<typename T, typename F>
struct my_condition<false, T, F> : my_type_identity<F> {};

template<bool cond, typename T, typename F>
using my_condition_t = my_condition<cond, T, F>::type;






int main()
{
    
    std::cout << sum <2,2>::value << std::endl;
    echo_type_t<float> result = 0.0f;

    static_assert(my_is_void<void>{});
    my_remove_const_t<int const> temp = 3;
    temp = 3+3;     //Because the cont has been removed by my_remove_const_t

    static_assert(is_same_v<float, my_condition_t<true, float, int>>);
    
    return 0;
}