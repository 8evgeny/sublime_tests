#include <chrono>
#include <iostream>
#include <thread>

void foo() { std::this_thread::sleep_for(std::chrono::seconds(1)); }

int main() {
  std::thread t;
  std::cout << "before starting, joinable: " << std::boolalpha << t.joinable()
            << '\n';

  t = std::thread(foo);
  std::cout << "after starting, joinable: " << t.joinable() << '\n';

  t.join();
  std::cout << "after joining, joinable: " << t.joinable() << '\n';
}
