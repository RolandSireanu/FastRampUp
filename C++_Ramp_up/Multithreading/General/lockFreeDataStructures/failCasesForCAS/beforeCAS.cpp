// Another thread modifies the shared variable after the current one reads the value but
// before it executes CAS operation

#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> sharedValue{0};

void incrementSharedValue() {
    int expected = sharedValue.load(); // Thread reads the current value
    // Simulate some work before CAS
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    while (!sharedValue.compare_exchange_weak(expected, expected + 1)) {
        // CAS failed, expected is updated with the current value
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