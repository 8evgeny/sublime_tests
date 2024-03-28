#include <future>
#include <iostream>

std::mutex m;
void worker() {
    std::lock_guard<std::mutex> guard(m); // Acquires a lock on the mutex
    // Synchronized code here
} // the mutex is automatically released when guard goes out of scope
void worker2() {
    // by default, constructing a unique_lock from a mutex will lock the mutex
    // by passing the std::defer_lock as a second argument, we
    // can construct the guard in an unlocked state instead and
    // manually lock later.
    std::unique_lock<std::mutex> guard(m, std::defer_lock);
    // the mutex is not locked yet!
    guard.lock();
    // critical section
    guard.unlock();
    // mutex is again released
}
int main()
{
#if 0
Thread synchronization can be accomplished using mutexes, among other synchronization primitives. There are
several mutex types provided by the standard library, but the simplest is std::mutex. To lock a mutex, you
construct a lock on it. The simplest lock type is std::lock_guard:
With std::lock_guard the mutex is locked for the whole lifetime of the lock object. In cases where you need to
manually control the regions for locking, use std::unique_lock instead:
#endif




}
