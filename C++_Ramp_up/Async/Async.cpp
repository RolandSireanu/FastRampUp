#include <iostream>
#include <thread>
#include <future>
#include <chrono>
using namespace std;
using namespace std::chrono;

//Async takes care of the multithreading programming overhead 
//It takes a callback and runs it concurrently or when it's result is requested

bool isPrime(int nr)
{
    for(int j = 2; j <= nr / 2; j++)
    {
        if(nr % j == 0)
        {
            return false;
        }
    }
    return true;
}

int prime(unsigned int start , unsigned int stop)
{
    unsigned int counter = 0;

    for(int i=start; i<stop; i++)
    {
        if(i < 2)
        {
            counter ++;
            continue;
        }
        
        if(isPrime(i))
        {
            counter++;

        }
        
    }

    return counter;
}
//#define SEQUENTIAL


int main()
{
    auto start = high_resolution_clock::now();
    #ifdef SEQUENTIAL
        cout << prime(1,1000000) << endl;
    #else 
    //Start 4 threads and spliting the workload
    //Don't care about thread join , reusing threads etc 
    future<int> res1 = std::async(std::launch::async, prime,1,250000);
    future<int> res2 = std::async(std::launch::async, prime,250000,500000);
    future<int> res3 = std::async(std::launch::async, prime,500000,750000);
    future<int> res4 = std::async(std::launch::async, prime,750000,1000000);
    res1.wait();
    res2.wait();
    res3.wait();
    res4.wait();
    cout << "Total = " << res1.get() + res2.get() + res3.get() + res4.get() << endl;
    #endif
    auto stop = high_resolution_clock::now();

    
    auto duration = duration_cast<microseconds>(stop - start); 
    cout << "Duration : " << duration.count() / 1000 << " ms" << endl;

    return 0;
}