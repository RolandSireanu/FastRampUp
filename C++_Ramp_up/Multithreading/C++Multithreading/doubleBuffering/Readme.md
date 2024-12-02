There are two types of mutexes:
    1. std::mutex
        allows only one thread to lock it at a time, providing exclusive access to a shared resource.
        Used togethet with:
            unique_lock
            lock_guard

    2. std::shared_mutex
         allows multiple threads to acquire shared (read) access while providing exclusive (write) access to one thread at a time.
         Used with:
            shared_lock
            This lock acquires shared (read) ownership of the mutex, allowing multiple threads to hold a shared_lock simultaneously while permitting only one thread to hold a unique_lock.

The power of shared_mutex
    Allows multiple threads to acquire a shared lock simultaneously for reading. However, it ensures that while any threads hold shared locks for reading, no thread can acquire an exclusive lock for writing.
    When a thread acquires a std::shared_lock, it indicates that the lock is shared, and the mutex guarantees that no modifications can occur until all shared locks are released.
    The read-only enforcement is down to programmer, it is not enforced in any way by the C++ runtime or compiler.

Condition variables.
Lock the mutex of a condition variable with unique_lock, why? 
Because ff an exception is thrown within the wait, wait_for, or wait_until function of the condition variable, unique_lock automatically unlocks the mutex.