#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <random>

constexpr int MAX_NR_OF_ENTRIES {1024};

typedef struct Request
{    
    int mStartInterval;
    int mEndInterval;
}Request_t;

typedef struct InBuffer
{
    std::queue<Request_t> mBuffer;
    std::mutex mMutex;
}InBuffer_t;

typedef struct OutBuffer
{    
    std::queue<int> mBuffer;
    std::mutex mMutex;
}OutBuffer_t;

InBuffer_t  gInBuffer;
OutBuffer_t gOutBuffer;
std::condition_variable gCondInputAvailable;
std::condition_variable gCondOutputAvailable;
std::condition_variable gCondSpaceInBuffer;
std::condition_variable gCondSpaceInOutBuffer;
thread_local Request_t gReq;

namespace WorkloadGenerator
{
    std::random_device lDev;
    std::mt19937 lRng(lDev());
    std::uniform_int_distribution<std::mt19937::result_type> lDist(1,1000000);

    inline int GenEndInterval()
    {
        return lDist(lDev);
    }
}

static bool isPrime(const int num) 
{
    if (num <= 1) 
    {
        return true;
    }
    if (num <= 3) 
    {
        return false;
    }

    for(int i=2; i<num; ++i)
    {
        if(num % i == 0)
        {
            return 0;
        }
    }

    return 1;
}

static int SumPrimeNumbers() 
{
    int sum = 0;

    for (int i = gReq.mStartInterval; i <= gReq.mEndInterval; ++i)
    {
        if (isPrime(i) == 1) 
        {
            sum += i;
        }
    }
    return sum;
}

void AddToInBuffer(const Request_t& aReq)
{
    std::unique_lock<std::mutex> lUniqueLock(gInBuffer.mMutex);
    gCondSpaceInBuffer.wait(lUniqueLock, []() -> bool{        
        return gInBuffer.mBuffer.size() < (MAX_NR_OF_ENTRIES);
    });
    gInBuffer.mBuffer.push(aReq);
    lUniqueLock.unlock();
    gCondInputAvailable.notify_one();
}

void AddToInBuffer(Request_t&& aReq)
{    
    std::unique_lock<std::mutex> lUniqueLock(gInBuffer.mMutex);    
    gCondSpaceInBuffer.wait(lUniqueLock, []() -> bool{        
        return gInBuffer.mBuffer.size() < (MAX_NR_OF_ENTRIES);
    });
    gInBuffer.mBuffer.emplace(std::forward<Request_t>(aReq));
    lUniqueLock.unlock();
    gCondInputAvailable.notify_one();
}

void AddToOutBuffer(const int& aValue)
{
    std::unique_lock<std::mutex> lUniqueLock(gOutBuffer.mMutex);
    gCondSpaceInOutBuffer.wait(lUniqueLock, [](){
        return gOutBuffer.mBuffer.size() < (MAX_NR_OF_ENTRIES);
    });
    gOutBuffer.mBuffer.push(aValue);
    lUniqueLock.unlock();
    gCondOutputAvailable.notify_one();
}

Request_t GetFromInBuffer()
{
    std::unique_lock<std::mutex> lUniqueLock(gInBuffer.mMutex);
    gCondInputAvailable.wait(lUniqueLock, [](){
        return gInBuffer.mBuffer.size() > 0;
    });
    Request_t lReq {gInBuffer.mBuffer.front()};
    gInBuffer.mBuffer.pop();
    lUniqueLock.unlock();
    gCondSpaceInBuffer.notify_one();

    return lReq;
}

int GetFromOutBuffer()
{
    std::unique_lock<std::mutex> lUniqueLock(gOutBuffer.mMutex);
    gCondOutputAvailable.wait(lUniqueLock, []() -> bool {
        return gOutBuffer.mBuffer.size() > 0;
    });
    const int lResult = gOutBuffer.mBuffer.front();
    gOutBuffer.mBuffer.pop();
    lUniqueLock.unlock();
    gCondSpaceInOutBuffer.notify_one();

    return lResult;
}

void Thread(int id)
{        
    while(1)
    {
        gReq = GetFromInBuffer();
        const int lResult {SumPrimeNumbers()};
        AddToOutBuffer(lResult);
    }
}

int main()
{
    using namespace std;

    constexpr int lNrOfThreads {14};    
    std::vector<thread> lArrayOfThreads(lNrOfThreads);

    for(int i{0}; i<MAX_NR_OF_ENTRIES/2; ++i)
    {
        AddToInBuffer(Request_t{.mStartInterval=0, .mEndInterval=static_cast<int>(WorkloadGenerator::GenEndInterval())});
    }

    for(int i{0}; i<lNrOfThreads; ++i)
    {
        lArrayOfThreads.emplace_back(Thread, i);
    }

    while(1)
    {
        int lRandomNr = WorkloadGenerator::GenEndInterval();
        AddToInBuffer(Request_t{.mStartInterval=0, .mEndInterval=lRandomNr});

        const int lResult = GetFromOutBuffer();
        // std::cout << "lResult = " << lResult << "\n";
    }

    for(auto& arg : lArrayOfThreads)
    {
        if(arg.joinable())
            arg.join();
    }

    return 0;
}