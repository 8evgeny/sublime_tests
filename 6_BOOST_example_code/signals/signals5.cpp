#include <boost/signals2.hpp>
#include <iostream>
using namespace boost::signals2;

float product(float x, float y) { return x * y; }
float quotient(float x, float y) { return x / y; }
float sum(float x, float y) { return x + y; }
float difference(float x, float y) { return x - y; }

int main() {
    boost::signals2::signal<float (float, float)> sig;

    sig.connect(&product);
    sig.connect(&quotient);
    sig.connect(&sum);
    sig.connect(&difference);

    // The default combiner returns a boost::optional containing the return
    // value of the last slot in the slot list, in this case the
    // difference function.
    std::cout << *sig(5, 3) << std::endl;

}
