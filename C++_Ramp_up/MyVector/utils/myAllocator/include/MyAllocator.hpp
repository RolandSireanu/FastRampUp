#ifndef MY_ALLOCATOR_HPP
#define MY_ALLOCATOR_HPP

template<typename T>
class MyAllocator
{
    using value_type =      T;
    using pointer =         T*;
    using const_pointer =   const pointer;
    using reference =       T&;
    using const_reference = const reference;
    using size_type =       std::size_t;
    using difference_type = std::ptrdiff_t;


public:    
    constexpr pointer allocate(size_type aNrOfBytes) { return reinterpret_cast<pointer>(::operator new(aNrOfBytes)); }
    void deallocate(pointer aPtr) { ::operator delete(aPtr); }
    pointer address(reference x) const noexcept { return &x; }
    template<typename U, typename ...Args>
    pointer construct(U* aPtr, Args ...aArgs) { return new ((void*)aPtr) U(std::forward<Args>(aArgs)...); }
    void destroy(pointer aPtr) { aPtr->~T(); }
};

#endif