/*
Another thread modifies the shared variable after the current thread starts preparing for the CAS but before it executes the CAS.
*/

#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> sharedValue{0};

void incrementSharedValue() {
    int expected = sharedValue.load(); // Thread reads the current value
    int desired = expected + 1;       // Thread computes the desired value
    // Simulate some work before CAS
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    while (!sharedValue.compare_exchange_weak(expected, desired)) {
        // CAS failed, expected is updated with the current value
        desired = expected + 1; // Recompute the desired value
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