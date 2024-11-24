Lock-free data structures in general have better performance because they allow multiple threads to operate on shared resources without waiting the locks to be release. This reduces the time threads spend blocked.

No deadlocks and enhanced scalability because they don't suffer from the overhead contention that locks introduce. No priority inversion problem.

Question 1
If multiple cores (threads) execute an atomic operation on the same memory area they will execute it sequentially, right?

    While one thread is executing an atomic operation, other threads that attempt to perform the same operation may be stalled. However, because the CAS operation is atomic, it will NOT LOCK THE ENTIRE DATA STRUCTURE or block other threads from performing operations on different parts of the structure.


    Lock-free data structures generally allow threads to proceed without being blocked by others. When a thread fails to complete an operation (for instance, if another thread updates the data structure), it can retry the operation. This retry mechanism allows other threads to continue executing operations concurrently on the same or different locations in memory.

    Reduced context switching

    Improved throughput
    Although individual atomic operation might seem to stall, the overall throughput increases
    as other threads may succesfully operate on other parts of data structure.

    In case of conflict, the atomic operation simply retry instead of beeing blocked.

How is the retry process implemented?
    It is based on certain hw atomic operations like (CAS or Load-Link/Store-Conditional)
    Steps in retry process:
        1. Read the current state
        2. CAS operatin check weather a certain memory location hold the expected value (read before)
            2.1 If it does, change the value to a new one atomically
            2.2 If it doesn't, because another thread made a chagen during the operation, than simply retry
                2.2.1 Re-read current state
                2.2.2 Re-evaluate condition and recalculating new value based on most recent data
                2.2.3 Atempt to do CAS atomically 
    Example:
    ThreadA read counter with value 10
    ThreadA performs the CAS operation:
        CAS check if value is still 10
        If it is, change value to 11 atomically and exit
        If it isn't, another thread made a change between "Read" and "CAS" operation
            Retry
