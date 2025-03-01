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

//#include <format>
#include <fmt/core.h>
#include <fmt/format.h>

#include <vector>
#include <thread>
#include <cmath>
#include <barrier>
using namespace std::literals;  // for duration literals

int main()
{
  // initialize and print a collection of floating-point values: 
  std::vector values{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

  // define a lambda function that prints all values
  // - NOTE: has to be noexcept to be used as barrier callback
  auto printValues = [&values] () noexcept{
                       for (auto val : values) {
                         std::cout << fmt::format(" {:<7.5}", val);
                       }
                       std::cout << '\n';
                     };
  // print initial values:
  printValues();
  
  // initialize a barrier that prints the values when all threads have done their computations:
  std::barrier allDone{int(values.size()),  // initial value of the counter
                       printValues};        // callback to call whenever the counter is 0

  // initialize a thread for each value to compute its square root in a loop:
  std::vector<std::jthread> threads;
  for (std::size_t idx = 0; idx < values.size(); ++idx) {
    threads.push_back(std::jthread{[idx, &values, &allDone] (std::stop_token st) {
                                     // repeatedly:
                                     while (!st.stop_requested()) {
                                       // compute square root:
                                       values[idx] = std::sqrt(values[idx]);
                                       std::this_thread::sleep_for(10ms * idx);
                                       // and synchronize with other threads to print values:
                                       allDone.arrive_and_wait();
                                     }
                                     // remove thread from counter so that other threads don't wait:
                                     allDone.arrive_and_drop();
                                   }});                       
  }
  //...

  // after a while/event destroy threads, which signals them to stop:
  std::this_thread::sleep_for(0.5s);
  std::cout << "\nSTOP\n";
  threads.clear();
  //...
}

