#include <future>
#include <iostream>
#include <thread>

void Print_threads_id()
{
    //Print this threads id
    std::cout << std::this_thread::get_id() << '\n';
}

void sleep_3_s()
{
    std::cout << "Waited for 3 seconds!\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void sleep_until()
{
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(2));
    std::cout << "We are now located 2 seconds after the thread has been called\n";
}

void foo(int a)
{
    for (int i = 0; i < a; ++i)
        std::this_thread::yield(); //Now other threads take priority, because this thread
    //isn't doing anything important
    std::cout << "Hello World!\n";
}



int main()
{
    Print_threads_id();
    std::thread thread1{ Print_threads_id };
    std::thread thread2{ Print_threads_id };
    std::thread thread3{ Print_threads_id };
    thread1.join();
    thread2.join();
    thread3.join();

    sleep_until();
    sleep_3_s();

    std::thread thread{ foo, 10 };
    thread.join();

}
