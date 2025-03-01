//********************************************************
// The following code example is taken from the book
//  C++20 - The Complete Guide
//  by Nicolai M. Josuttis (www.josuttis.com)
//  http://www.cppstd20.com
//
// The code is licensed under a
//  Creative Commons Attribution 4.0 International License
//  http://creativecommons.org/licenses/by/4.0/
//********************************************************


#include <iostream>
#include <array>
#include <vector>
#include <thread>
#include <latch>
using namespace std::literals;  // for duration literals

int main()
{
  std::size_t numThreads = 10;

  // initialize latch to start the threads when all of them have been initialized:
  std::latch allReady{10};   // initialize countdown with number of threads

  // start numThreads threads:
  std::vector<std::jthread> threads;
  for (int i = 0; i < numThreads; ++i) {
    std::jthread t{[i, &allReady] {
                     // initialize each thread (simulate to take some time):
                     std::this_thread::sleep_for(100ms * i);
                     //...
                     // synchronize threads so that all start together here:
                     allReady.arrive_and_wait(); // count_down() and wait()

                     // perform whatever the thread does
                     // (loop printing its index):
                     for (int j = 0; j < i + 5; ++j) {
                       std::cout.put(static_cast<char>('0' + i)).flush();
                       std::this_thread::sleep_for(50ms);
                     }
                   }};
    threads.push_back(std::move(t));
  }
  //...

  //Принудительно ожидаю присоединения чтобы быдать endl
  for (auto &i:threads)
    i.join();
  std::cout << std::endl;
}

