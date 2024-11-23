Memory barriers also known as memory fences are low level mechanism used in multi-core systems to enforce ordering constraints on the memory operations like LDR and STR.
In a nutshell, a memory barrier make sure that all memory operations specified before the barrier are completed before any memory operations that follow the barrier.
The compiler can reorder the instructions before and after the barrier but never over the barrier, like one instruction that was before the barrier to be scheduled after the barrier.

They are critical in multi-threaded environments where threads share data and need to synchronize their access to avoid inconsistencies.
* Types of Barriers:REA
    1. Load Barrier: Ensures that all load (read) operations before the barrier are completed before any load operations after the barrier.
    2. Store Barrier: Ensures that all store (write) operations before the barrier are completed before any store operations after the barrier.
	3	Full Barrier: Ensures that all load and store operations before the barrier are completed before any load and store operations after the barrier.

Syntax for memory barrier :   asm volatile("" ::: "memory");

As we have seen, processor optimizations such as caches, write buffers and out-of-order execution can result in memory operations occurring in an order different from that specified in the executing code.

Example:
￼  ![Example] ("./Example.png")
There are 4 possible outcomes depending on the order of execution choose by the compiler:

* A gets the old value, B gets the old value.
* A gets the old value, B gets the new value.
* A gets the new value, B gets the old value.
* A gets the new value, B gets the new value.

By putting a memory fence between STR and LDR:
	STR R0, [Addr1]
	asm volatile("" ::: "memory");
	LDR R1, [Addr2]
You enforce a strict ordering between the two, LDR instruction will be executed only after STR is globally visible.

Memory barriers in pthread standard:
Where are memory barriers used in pthreads standard?
1. Mutexes:
    * When a thread acquires or releases a mutex using pthread_mutex_lock() or pthread_mutex_unlock(), memory barriers are used to ensure that all memory operations (reads and writes) that occurred before the lock is unlocked are visible to all threads that subsequently acquire that lock.
    * This guarantees that any data modified while a mutex is held is correctly seen by another thread that later acquires that same mutex.
2. Condition Variables:
    * In pthread_cond_wait() and pthread_cond_signal(), memory barriers are used to ensure that changes made to shared variables are visible to other threads. For instance, when a thread waits on a condition variable, it must release the associated mutex and ensure that all changes made to shared data are visible before it waits.
    * Conversely, when signaling a condition variable with pthread_cond_signal(), the memory barrier ensures that any prior writes made by the signaling thread are visible to the thread that receives the signal.


Links:
https://developer.arm.com/documentation/den0042/a/Memory-Ordering/Memory-barriers
https://preshing.com/20120515/memory-reordering-caught-in-the-act/