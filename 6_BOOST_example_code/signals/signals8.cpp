#include <boost/signals2.hpp>
#include <iostream>
using namespace boost::signals2;
struct HelloWorld {
  void operator()() const { std::cout << "Hello, World!" << std::endl; }
};
int main() {
  boost::signals2::signal<void()> sig;
  boost::signals2::connection c = sig.connect(HelloWorld());
  std::cout << "c is connected\n";
  sig();  // Prints "Hello, World!"

  c.disconnect();  // Disconnect the HelloWorld object
  std::cout << "c is disconnected\n";
  sig();  // Does nothing: there are no connected slots

  boost::signals2::connection cc = sig.connect(HelloWorld());
  std::cout << "cc is not blocked.\n";
  sig();  // Prints "Hello, World!"

  {
    boost::signals2::shared_connection_block block(cc);  // block the slot
    std::cout << "cc is blocked.\n";
    sig();  // No output: the slot is blocked
  }         // shared_connection_block going out of scope unblocks the slot
  std::cout << "cc is not blocked.\n";
  sig();  // Prints "Hello, World!"}
}
