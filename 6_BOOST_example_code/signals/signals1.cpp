#include <boost/signals2.hpp>
#include <iostream>
using namespace boost::signals2;
using namespace std;

struct HelloWorld {
  void operator()() const { std::cout << "Hello, World!" << std::endl; }
};

int main() {
  // Signal with no arguments and a void return value
  boost::signals2::signal<void()> sig1, sig2;

  // Connect a HelloWorld slot
  HelloWorld hello1;
  HelloWorld hello2;
  sig1.connect(hello1);
  sig2.connect(hello1);
  sig2.connect(hello2);
  // Call all of the slots
  sig1();
  cout << sig1.num_slots() << std::endl;
  sig2();
  cout << sig2.num_slots() << std::endl;
}
