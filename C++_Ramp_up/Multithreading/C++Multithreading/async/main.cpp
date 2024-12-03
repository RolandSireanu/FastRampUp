#include <iostream>
#include <future>
#include <thread>
#include <chrono>

/*
    Asynchronous programming shines in I/O-bound applications, while multithreading can be more suitable for CPU-bound tasks that can genuinely benefit from parallel execution.
*/

bool readFromIO()
{
    int counter {0};

    while(counter < 1000)
    {
        std::cout << "Reading from IO ... counter = " << counter << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        counter += 50;
    }

    return true;
}

int main()
{
    std::future<bool> backgroundThread = std::async(std::launch::async, readFromIO);
    std::future_status status;
    while(true)
    {
        std::cout << "Main thread running ... \n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        status = backgroundThread.wait_for(std::chrono::milliseconds(1));

        if(status == std::future_status::ready)
        {
            std::cout << "Data ready! \n";
            break;
        }
    }

    std::cout << "Exit main thread \n";


    return 0;
}