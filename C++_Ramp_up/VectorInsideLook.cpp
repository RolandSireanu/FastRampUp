#include <iostream>
#include <vector>
#include <array>
#include <initializer_list>
#include <memory>
#include <cstring>
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

// ======================== Function Template Overloading ==============================
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
//Two template functions that generate overloads for the same my_make_unique
//Enable_if will assure that only one template will be used at a time to generate my_make_unique
// ======================================================================================

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
    class Iterator;
    class ConstIterator;
public:
    using value_type = T;
    using reference_type = T&;
    using const_reference = const T&;
    using pointer = T*;
    using size_type = size_t;
    using iterator = Iterator;
    using const_iterator = ConstIterator;
    static constexpr int32_t scaleFactor = 2;
    
    //The Iterator should be copy-constructible/assignable and swappable
    class Iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator(pointer aData) : mData{aData} {}
        Iterator(MyVector const& aVec) : mData{aVec.mPtrData} {}
        reference operator*() { return *mData; }
        pointer operator->()  { return mData;  }
        Iterator& operator++() { mData++; return *this; }
        Iterator& operator++(int) {Iterator& orig = *this; ++(*this); return orig; }

        friend bool operator==(const Iterator& lhs, const Iterator& rhs) { return lhs.mData == rhs.mData; }
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return lhs.mData != rhs.mData; }
    private:
        pointer mData;
    };

    class ConstIterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = const T*;
        using reference = const T&;

        explicit ConstIterator(pointer aData) : mData{aData} {}
        ConstIterator(MyVector const& aVec) : mData{aVec.mPtrData} {}
        reference operator*() const { return *mData; }
        pointer operator->()  const { return mData;  }
        ConstIterator& operator++() { mData++; return *this; }
        ConstIterator& operator++(int) {Iterator& orig = *this; ++(*this); return orig; }

        friend bool operator==(const ConstIterator& lhs, const ConstIterator& rhs) { return lhs.mData == rhs.mData; }
        friend bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs) { return lhs.mData != rhs.mData; }
        friend bool operator>(const ConstIterator& lhs, const ConstIterator& rhs)  { return lhs.mData > rhs.mData; }
        friend bool operator<(const ConstIterator& lhs, const ConstIterator& rhs)  { return lhs.mData < rhs.mData; }
    private:
        pointer mData;
    };

    MyVector(std::initializer_list<value_type> aElements) : mPtrData{}
    {
        int32_t index {0};
        for(const auto& e : aElements)
        {
            mPtrData[index] = e;
            index++;
        }
        mCurrentPos = index;
    }

    explicit MyVector(size_type aCount, const_reference aElement) : mSize{aCount*scaleFactor}, mPtrData{mAllocator.allocate(mSize)}
    {
        for(int i{0}; i<aCount; i++)
        {
            mPtrData[i] = aElement;
        }
        mCurrentPos = aCount;
    }

    template<typename InputIt, typename = typename my_enable_if<my_is_iterator<InputIt>::value>::type>
    MyVector(InputIt first, InputIt last)
    {
        int32_t index {0};
        for(InputIt it = first; it != last; it++)
        {
            mPtrData[index] = *it;
            index++;
        }
        mCurrentPos = index;
    }

    reference_type operator[](size_type aPos) { return mPtrData[aPos]; }
    iterator begin() { return iterator{mPtrData}; }
    iterator end() { return iterator{mPtrData + mSize}; }
    const_iterator cbegin() { return const_iterator{mPtrData}; }
    const_iterator cend() { return const_iterator{mPtrData + mSize}; }

    void resize(size_type aCount)
    {
        if(aCount > mSize)
        {
            pointer lTemp = mAllocator.allocate(aCount);

            for(int i{0}; i<mSize; ++i)
            {
                lTemp[i] = std::move(mPtrData[i]);
            }
            delete mPtrData;
            mPtrData = lTemp;
            mSize = aCount;
        }
    }

    void push_back(const T& aElement)
    {        
    }

    ~MyVector() noexcept
    {
        mAllocator.deallocate(mPtrData, mSize);
    }

private:
    size_type mSize {0};
    size_type mCurrentPos {0};
    Allocator mAllocator{};
    pointer mPtrData;
};

template<typename T>
auto begin(MyVector<T> const& aVector) { return aVector.begin(); }
template<typename T>
auto end(MyVector<T> const& aVector) {return aVector.end(); }    
template<typename T>
auto cbegin(MyVector<T> const& aVector) ->decltype(aVector.cbegin()) { return aVector.cbegin(); }
template<typename T>
auto cend(MyVector<T> const& aVector) -> decltype(aVector.cend()) { return aVector.cend(); }

int main()
{
    MyVector m(10,10);
    m[0] = 12;
    std::cout << m[0] << " , " << m[1] << " , " << m[2] << std::endl;
    m.resize(30);
    // MyVector m2{1,2,3,4,5};
    // m2[1] = m[2];

    // array<int,5> a {10,20,30,40,50};
    // MyVector<int> m3(a.begin(), a.end());

    for(const auto& e : m)
        std::cout << e << std::endl;    
    
    


    return 0;
}
