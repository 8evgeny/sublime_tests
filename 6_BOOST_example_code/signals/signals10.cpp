#include <boost/signals2.hpp>
#include <iostream>
using namespace boost::signals2;

void foo() { std::cout << "foo"; }
void bar() { std::cout << "bar\n"; }

int main() {
    boost::signals2::signal<void ()> sig;
    sig.connect(&foo);
    sig.connect(&bar);
    sig();

    // disconnects foo, but not bar
    sig.disconnect(&foo);
    sig();
}
