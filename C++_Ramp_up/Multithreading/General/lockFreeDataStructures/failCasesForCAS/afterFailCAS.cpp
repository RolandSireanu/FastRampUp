/*
Another thread modifies the shared variable after the current thread’s CAS fails but before it retries.
*/

#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> sharedValue{0};

void incrementSharedValue() {
    int expected = sharedValue.load(); // Thread reads the current value
    while (!sharedValue.compare_exchange_weak(expected, expected + 1)) {
        // CAS failed, expected is updated with the current value
        // Simulate some work before retrying
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main() {
    std::thread t1(incrementSharedValue);
    std::thread t2(incrementSharedValue);

    t1.join();
    t2.join();

    std::cout << "Final value: " << sharedValue.load() << std::endl;
    return 0;
}