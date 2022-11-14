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

//remove const metafunction
template<typename T>
struct my_remove_const : my_type_identity<T> {};
template<typename T>
struct my_remove_const<T const> : my_type_identity<T> {};
template<typename T>
using my_remove_const_t = my_remove_const<T>::type;

//remove volatile metafunction
template<typename T>
struct my_remove_volatile : my_type_identity<T> {};
template<typename T>
struct my_remove_volatile<T volatile> : my_type_identity<T> {};

//remove cv metafunction
template<typename T>
using my_remove_cv = my_remove_volatile<my_remove_const_t<T>>;
template<typename T>
using my_remove_cv_t = my_remove_cv<T>::type;


// Conditional metafunction, returns a type or another, 
// depending on the condition evaluation
template<bool cond, typename T, typename F>
struct my_condition : my_type_identity<T> {};
template<typename T, typename F>
struct my_condition<false, T, F> : my_type_identity<F> {};
template<bool cond, typename T, typename F>
using my_condition_t = my_condition<cond, T, F>::type;


//is_same metafunction
template<typename T1, typename T2>
struct my_is_same : my_false_type {};
template<typename T1>
struct my_is_same<T1,T1> : my_true_type {};
template<typename T1, typename T2>
constexpr auto my_is_same_v = my_is_same<T1, T2>::value;

//is_pointer metafunction
template<typename T>
struct my_is_pointer : my_false_type {};
template<typename T>
struct my_is_pointer<T*> : my_true_type {};
template<typename T>
constexpr bool my_is_pointer_v = my_is_pointer<my_remove_cv_t<T>>::value;


// =============== Function overload resolution =========================
my_true_type my_is_nullptr(nullptr_t);
my_false_type my_is_nullptr(...);
template<typename T>
using is_null_ptr = decltype(my_is_nullptr(declval<T>()));

template<typename T1, typename T2>
struct no_diff 
{
    static constexpr bool value = false;
};


template<typename T1>
struct no_diff<T1, void>
{
    static constexpr bool value = true;
};


int main()
{
    
    std::cout << sum <2,2>::value << std::endl;
    echo_type_t<float> result = 0.0f;

    static_assert(my_is_void<void>{});
    my_remove_const_t<int const> temp = 3;
    temp = 3+3;     //Because the cont has been removed by my_remove_const_t

    static_assert(my_is_same_v<float, my_condition_t<true, float, int>>);
    static_assert(my_is_pointer<int* >::value);
    static_assert(is_null_ptr<nullptr_t>::value);
    static_assert(no_diff<int, void>::value);
    return 0;
}