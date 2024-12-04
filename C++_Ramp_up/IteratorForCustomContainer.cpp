#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */
#include <string.h>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <memory>
#include<bits/stdc++.h>
using namespace std;

// ==========================  ITERATORS ====================
// An iterator is an object that points to an element inside a container.
// It can move forward and backward based on its properties. 
// All the operations suported by a pointer are implemented in the iterator api (*,->,++,--)

// Iterators are also useful when you want to iterate over elements of a custom container
// that you wrote yourself. Adding iterators to your container will make it compatible with
// RANGE-BAED-FOR-LOOPS and the ALGORITHMS library.

class Container
{
    struct Iterator
    {
        // ===== Properties of the iterator ====
        // iterator_categoy can take values from [InputIterator, OutputIterator, ForwardIterator, BidirectionalIterator, RandomAccessIterator, ContiguousIterator]
        // tags are used to select the most efficient algorithm if your container is passed to one of STL algorithm function.
        // for example, std::fill wants a ForwardIterator, std::reverse wants a Bidirectional iterator
        using iterator_category = std::forward_iterator_tag;
        //Type used to identify the distance between two iterators, our iterator is a wrapper around a pointer
        //and it leverages pointer arithmetic so the ptrdiff_t is a good choice.
        using difference_type = std::ptrdiff_t;
        using value_type = int;
        using pointer = int*;
        using reference = int&;

        // ALL ITERATORS SHOULD BE: Constructible, copy-constructible, copy-assignable, destructible, swappable

        Iterator(pointer arg_p):m_ptr(arg_p) {}

        reference operator*() const 
        {
            return *m_ptr;
        }

        pointer operator->()
        {
            return m_ptr;
        }

        Iterator& operator++()
        {
            m_ptr++;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            m_ptr++;
            return temp;
        }

        friend bool operator==(const Iterator& lhs, const Iterator& rhs) { return lhs.m_ptr == rhs.m_ptr; }
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return lhs.m_ptr != rhs.m_ptr; }

        private:
            pointer m_ptr;

    };

    public:
        Iterator begin() { return Iterator(m_data); }
        Iterator end() { return Iterator(m_data+MAX_SIZE); }

    private:
        static constexpr std::size_t MAX_SIZE = 8;
        int m_data[MAX_SIZE];
};

// Strictly for a simple array, you need just a simple Iterator with begin and end methods
// class Itegers
// {
//     using IntegersType = std::array<int,32>;

//     public:
//         IntegersType::iterator begin() { return m_data.begin(); }
//         IntegersType::iterator end() { return m_data.end(); }

//     private:
//         IntegersType m_data;
// };


Container container;

int main ()
{
    std::fill(container.begin(), container.end(), 0xff);

    //This range based for loop is just syntatic sugar for :
    //for(Container::Iterator it=container.begin(); it!=container.end(); ++it)
    for(const auto& e : container)
        cout <<" E = " << e << endl;

    auto it = container.begin();
    *it = 22;

  return 0;
}

// Iterator behaves just like a pointer, how should I use it ?
// We could get ride of the while Iterator class and just return a raw pointer to first and last
// elements of the array, from Container::begin, Container::end. Range based for loop and algorithms 
// would work just fine. The problem is that real world containers are often based on more
// complex data structures like lists, trees, maps etc. Iterator abstract away all the complexity
// behind an object that behaves like a pointer and let you access a complex data structure with familiar operations.