


#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */
#include <string.h>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <memory>
#include <queue>
using namespace std;

// ============ Find the k-th largest element in array using min heap =======


template<typename T>
void printHeap(T arg_pq)
{    
    while(arg_pq.empty() == false)
    {
        cout << arg_pq.top() << " ";
        arg_pq.pop();
    }
    cout << endl;
}

template<typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;

template<typename T>
using max_heap = priority_queue<T, vector<T>, greater<T>>;

int main ()
{    
    unsigned int k = 2;
    vector<int> numbers {0,10,7,2,4,9};
    min_heap<int> mh(numbers.begin(), numbers.begin()+k);
    
    for(auto it=numbers.begin()+k; it!=numbers.end(); ++it)
    {
        if(*it > mh.top())
        {
            mh.pop();
            mh.push(*it);
        }
        printHeap(mh);
    }

    // printHeap(mh);


    

  return 0;
}
