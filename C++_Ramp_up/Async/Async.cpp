#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <vector>
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
    const int nrOfThreads = 16;
    const int workload = 1000000;
    const int resolution = workload / nrOfThreads;
    std::vector<std::future<int> > v(nrOfThreads);

    for(int i=0; i<nrOfThreads; i++)
    {
        v[i] = std::async(std::launch::async, prime,i*resolution,(i*resolution+resolution));    
    }

    for(int i=0; i<nrOfThreads; i++)
        v[i].wait();

    unsigned int sum = 0;
    for(int i=0; i<nrOfThreads; i++)
        sum = sum + v[i].get();
    
    cout << "Total = " << sum << endl;
    #endif
    auto stop = high_resolution_clock::now();

    
    auto duration = duration_cast<microseconds>(stop - start); 
    cout << "Duration : " << duration.count() / 1000 << " ms" << endl;

    return 0;
}