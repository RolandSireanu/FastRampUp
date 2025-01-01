#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// ========================= Promise & Future ========================================================
// A better way for communication and sharing data between threads.
// The sending end of the channel is called “promise” while the receiving end is called “future”.
// Each std::promise object is meant to be used only a single time
// Promises can not be copied, because the promise-future concept is a two-point communication channel for one-time us

void worker(std::promise<int>&& aPromise, int32_t aBoundary)
{
    using namespace std::chrono_literals;

    try
    {
        if(aBoundary < 0)
            throw std::runtime_error("Negative arguments are not allowed to worker thread!");

        int32_t lSum{};
        for(int32_t i{0}; i<aBoundary; ++i)
        {
            lSum += i;
        }
        std::this_thread::sleep_for(5000ms);

        aPromise.set_value(lSum);
    }
    catch(const std::exception& e)
    {        
        aPromise.set_exception(std::current_exception());
    }    
}


int main()
{
    std::promise<int32_t> lPromise;
    std::future<int32_t> lFuture = lPromise.get_future();
    std::thread lTh1 (worker, std::move(lPromise), -1024);
    
    std::cout << "Do some work meanwhile ... \n";
    std::cout << "Waiting for worker result \n";
    //Start listening on the other end of the communication channel by calling the function get() on the future. 
    //This method will block until data is available - which happens as soon as set_value has been called on the promise (from the thread).
    try
    {
        std::cout << "Result of working thread is " << lFuture.get() << "\n";        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    lTh1.join();

    return 0;
}