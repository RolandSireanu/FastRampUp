# What is a spinlock
It acts like a mutex but instead of putting the thread to sleep it does busy-waiting.
The downside is that it can waste cpu cycles.
Spinlocks usually provide a lightweight and fast way for threads to acquire and release locks, making them useful for <b>short critical sections</b>.
Another advantage is that it introduce low overheader compared with traditional locking mechanism on mutexes.