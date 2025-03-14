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


#include <fstream>
#include <cmath>
#include <thread>
#include <syncstream>
#include <iostream>

void squareRoots(std::ostream& strm, int num)
{
  std::osyncstream syncStrm{strm};
  for (int i = 0; i < num ; ++i) {
    syncStrm << "squareroot of " << i << " thread_" <<std::this_thread::get_id() << " is "
             << std::sqrt(i) << '\n' << std::flush_emit;

  }
}

int main()
{
  std::ofstream fs{"tmp.out"};
  std::jthread t1(squareRoots, std::ref(fs), 15);
  std::jthread t2(squareRoots, std::ref(fs), 5);
  std::jthread t3(squareRoots, std::ref(fs), 5);
  //Чтобы вывести содержимое надо сперва присоединить потоки
  t1.join();
  t2.join();
  t3.join();
  std::ifstream fs1{"tmp.out"};
  std::cout<<fs1.rdbuf()<<std::endl;
  std::cout<<std::endl;
}

