#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

class ThreadSafeCounter
{
    mutable std::shared_timed_mutex mutex_;
    int value_ = 0;
public:
    int get() const
    {
        std::shared_lock<std::shared_timed_mutex> lock(mutex_);
        return value_;
    }

    auto increment()
    {
        std::unique_lock<std::shared_timed_mutex> lock(mutex_);
        return ++value_;
    }
};

int main()
{
    ThreadSafeCounter counter;

    auto increment_and_print = [&counter]() {
        for (int i = 0; i < 3; i++) {
            counter.increment();
            std::cout << counter.get() << std::endl;

            // std::cout << std::this_thread::get_id() << " "
                      // << counter.get() << std::endl;
        }
    };

    std::thread thread1(increment_and_print);
    std::thread thread2(increment_and_print);

    thread1.join();
    thread2.join();
}
