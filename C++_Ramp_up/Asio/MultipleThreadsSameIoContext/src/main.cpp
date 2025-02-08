#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <thread>

using namespace boost;

// Function executed by multiple threads at once
void print(const boost::system::error_code& e, int id)
{
    std::cout << "Hello, world from thread " << std::this_thread::get_id()  << " internal id " << id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "Good bye, from thread " << std::this_thread::get_id()  << " internal id " << id << std::endl;
}

int main()
{
    asio::io_context io;
    asio::steady_timer t(io, asio::chrono::seconds(2));
    asio::steady_timer t2(io, asio::chrono::seconds(2));
    asio::steady_timer t3(io, asio::chrono::seconds(2));
    asio::steady_timer t4(io, asio::chrono::seconds(2));
    asio::steady_timer t5(io, asio::chrono::seconds(2));
    system::error_code e;

    // Print main thread id
    std::cout << "Main thread id: " << std::this_thread::get_id() << std::endl;

    int id {2};
    t.async_wait(boost::bind(print, asio::placeholders::error, 2));
    t2.async_wait(boost::bind(print, asio::placeholders::error, 4));
    t3.async_wait(boost::bind(print, asio::placeholders::error, 6));
    t4.async_wait(boost::bind(print, asio::placeholders::error, 8));
    t5.async_wait(boost::bind(print, asio::placeholders::error, 10));

    std::thread myThread([&io](){
    // Print current thread id
        std::cout << "Second thread id: " << std::this_thread::get_id() << std::endl;
        io.run();
    });

    std::thread myThread2([&io](){
    // Print current thread id
        std::cout << "Third thread id: " << std::this_thread::get_id() << std::endl;
        io.run();
    });

    io.run();

    myThread.join();
    myThread2.join();

    return 0;

}