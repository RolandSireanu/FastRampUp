#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP
#include <memory>

template<typename T, typename Allocator = std::allocator<T>>
class MyVector
{
    using value_type =              T;
    using allocator_type =          Allocator;
    using size_type =               std::size_t;
    using difference_type =         std::ptrdiff_t;
    using reference =               value_type&;
    using const_reference =         const reference&;
    using pointer =                 value_type*;
    using const_pointer =           const value_type*;

public:

    explicit MyVector(size_type aNrOfElements) {}
    MyVector(size_type aNrOfElements, const_reference aValue) {}
    explicit MyVector(std::initializer_list<T> aInitList) {}
    
    template<typename InputIt>
    MyVector(InputIt aFirst, InputIt aLast) {}

    MyVector() noexcept : MyVector(Allocator()) {}
    MyVector(const MyVector& aVector) = default;
    MyVector(MyVector&& aVector) = default;
    MyVector& operator=(const MyVector& aVector) = default;
    MyVector& operator=(MyVector&& aVector) = default;
    MyVector& operator=(std::initializer_list<T> aInitList) {}
    
    explicit MyVector(const Allocator& aAllocator = Allocator()) {}

    void assign(size_type aNrOfElements, const_reference aValue) {}
    template<typename InputIt>
    void assign(InputIt aFirst, InputIt aLast) {}
    void assign(std::initializer_list<T> aInitList) {}
    
    const_reference at(size_type aIndex) {}
    const_reference operator[](size_type aIndex) const {}
    reference operator[](size_type aIndex) {}

    const_reference front() const {}
    reference front() {}
    const_reference back() const {}
    reference back() {}

    const_pointer data() const {}
    pointer data() const {}


};

#endif