#include <iostream>
#include <vector>
#include <array>
#include <initializer_list>
#include <memory>
using namespace std;




template<class T, T v> struct my_integral_constant {static constexpr T value = v;};
template<bool v> using my_bool_constant = my_integral_constant<bool, v>;
using my_true_type = my_bool_constant<true>;
using my_false_type = my_bool_constant<false>;

template<typename T> struct my_is_lvalue_reference : my_false_type {};
template<typename T> struct my_is_lvalue_reference<T&> : my_true_type {};
template<typename T> struct my_is_rvalue_reference : my_false_type {};
template<typename T> struct my_is_rvalue_reference<T&&> : my_true_type {};

//TODO work to do
template<typename T, typename = void> struct my_is_iterator : my_false_type {};
template<typename T> struct my_is_iterator<T, decltype(*std::declval<T>(), void())> : my_true_type {};

template<typename T>
struct my_is_array
{
	static constexpr bool value {false};
};

template<typename T>
struct my_is_array<T[]>
{
	static constexpr bool value {true};
};

template<typename T, int N>
struct my_is_array<T[N]>
{
	static constexpr bool value {true};
};

template<typename T>
struct my_remove_extent
{
    using type = T;
};

template<typename T>
struct my_remove_extent<T[]>
{
	using type = T;
};

template<typename T, int N>
struct my_remove_extent<T[N]>
{
	using type = T;
};

template<bool cond, typename T = int> struct my_enable_if {};
template<typename T> struct my_enable_if<true, T> {using type = T;};

template<typename T> struct my_remove_reference {using type = T;};
template<typename T> struct my_remove_reference<T&> {using type = T;};
template<typename T> struct my_remove_reference<T&&> {using type = T;};

template<typename T> typename my_remove_reference<T>::type&& my_move(T&& arg) {return static_cast<typename my_remove_reference<T>::type&&>(arg);}

template<typename T, typename ... Args, typename=typename my_enable_if<!my_is_array<T>::value>::type >
unique_ptr<T> my_make_unique(Args... args)
{
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<typename T, typename = enable_if_t<my_is_array<T>::value>>
unique_ptr<T> my_make_unique(size_t size)
{
    return unique_ptr<T>(new typename my_remove_extent<T>::type[size]);
}

template<typename T>
T&& my_forward(typename my_remove_reference<T>::type& arg)
{
    return static_cast<T&&>(arg);
}

template<typename T>
T&& my_forward(typename my_remove_reference<T>::type&& arg)
{
    static_assert(!my_is_lvalue_reference<T>::value, "You can't have rvalue reference argument but lvalue ref type");
    return static_cast<T&&>(arg);
}


// T must be CopyAssignable an CopyConstrutible
template<typename T, typename Allocator = std::allocator<T>>
class MyVector
{
public:
    using value_type = T;
    using reference_type = T&;
    using const_reference = const T&;
    using pointer = unique_ptr<value_type[]>;
    using size_type = size_t;
    static constexpr int32_t scaleFactor = 2;

    MyVector(std::initializer_list<value_type> aElements) : mPtrData{my_make_unique<value_type[]>(aElements.size()*scaleFactor)}
    {
        int32_t index {0};
        for(const auto& e : aElements)
        {
            mPtrData[index] = e;
            index++;
        }
    }

    explicit MyVector(size_type aCount, const_reference aElement) :mPtrData{my_make_unique<value_type[]>(aCount*scaleFactor)}
    {
        for(int i{0}; i<aCount; i++)
        {
            mPtrData[i] = aElement;
        }
    }

    template<typename InputIt, typename = enable_if_t<my_is_iterator<InputIt>::value>>
    MyVector(InputIt first, InputIt last)
    {
        int32_t index {0};
        for(InputIt it = first; it != last; it++)
        {
            mPtrData[index] = *it;
            index++;
        }
    }

    reference_type operator[](size_type aPos)
    {
        return mPtrData[aPos];
    }

    pointer mPtrData;
};

int main()
{
    MyVector m(10,10);
    MyVector m2{1,2,3,4,5};
    m2[1] = m[2];
    std::cout << m2[1] << std::endl;

    array<int,5> a {10,20,30,40,50};
    MyVector<int> m3(a.begin(), a.end());


    return 0;
}
