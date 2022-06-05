#include <future>
#include <iostream>

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

void sleep_until_2_s()
{
    std::cout << "Waited until 2 seconds!\n";
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(2));
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

    sleep_3_s();
    sleep_until_2_s();

}
