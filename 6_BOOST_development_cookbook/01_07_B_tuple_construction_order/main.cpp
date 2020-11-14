#include <boost/tuple/tuple.hpp>
#include <iostream>

template <int I>
struct printer {
    printer() { std::cout << I<<std::endl; }
};

int main() {
    // Outputs 012
    boost::tuple<printer<0>, printer<1>, printer<2> > t;
    (void)t;
}
