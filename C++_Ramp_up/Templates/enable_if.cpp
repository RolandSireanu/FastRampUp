#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */
#include <string.h>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <memory>
#include <type_traits>
using namespace std;

constexpr unsigned int MAX = 512;
unsigned int container[MAX];
unsigned int counter = 0;

template<typename T, class = typename enable_if<is_pointer<T>{} || is_class<T>{}, T>::type >
void populate(T iter1, T iter2)
{
    for(auto it=iter1; it != iter2; it++)
    {
        container[counter] = *it;
        counter++;
    }
}


// non-type template parameter
template<typename T, enable_if_t<is_integral_v<T>, int> = 0>
void populate(T howMany, T value)
{
    unsigned int copyCounter = counter;
    for(int i=counter; i<counter+howMany; i++)
    {
        container[i] = value;
        copyCounter++;
    }

    counter = copyCounter;
    
}

int main ()
{
    unsigned int temp[5] {1,2,3,4,5};
    populate(temp, temp+4);

    vector<int> tempV {1,2,3,4,5};
    populate(tempV.begin(), tempV.end());

    populate(5,9);

    
    for(int i=0; i<counter; i++)
        cout << container[i] << " ";


    return 0;
}