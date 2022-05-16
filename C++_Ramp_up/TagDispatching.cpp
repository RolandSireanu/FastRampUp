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

// ==================== TAG DISPATCHING ======================
// What is a tag ?
// Data type with no data and no behavior
// strunct MyTag {}

// When it is useful ? 
// When we need several ways to build an object for the same set of parameters. 
// By creating several tags we can use them to route the execution through various overloads of a function

// Example : STL algorithms have difference behaviours based on the capabilities of the iterator type
// std::advance function, takes an iterator and moves it forward by a given number.
// If tghe underlying iterator of the collection is a forwared iterator then std::advance applies
// ++ operator three times. If it is a random-access iterator, it calls += 3 on it.
 
// Possible implementation of std::advance
template <typename Iterator, typename Distance>
void advance_impl(Iterator& it, Distance n, forward_iterator_tag)
{
    while (--n >= 0)
        ++it;
}

template <typename Iterator, typename Distance>
void advance_impl(Iterator& it, Distance n, random_iterator_tag)
{
    it += n;
}



int main ()
{
  return 0;
}