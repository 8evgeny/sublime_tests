#include <boost/signals2.hpp>
#include <iostream>
using namespace boost::signals2;

struct ShortLived {
  void operator()() const { std::cout << "Hello, World!" << std::endl; }
};

int main() {
  boost::signals2::signal<void()> sig;
  {
    boost::signals2::scoped_connection c(sig.connect(ShortLived()));
    sig();  // will call ShortLived function object
  }         // scoped_connection goes out of scope and disconnects

  sig();  // ShortLived function object no longer connected to sig

  // doesn't compile due to compiler attempting to copy a temporary
  // scoped_connection object boost::signals2::scoped_connection c0 =
  // sig.connect(ShortLived());

  // okay
  boost::signals2::scoped_connection c1(sig.connect(ShortLived()));

  // also okay
  boost::signals2::scoped_connection c2;
  c2 = sig.connect(ShortLived());
}
