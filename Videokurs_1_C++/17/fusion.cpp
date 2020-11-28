// Fusion
// Hana, MPL

#include <iostream>

#include <boost/fusion/tuple.hpp>
#include <boost/fusion/algorithm.hpp>
#include <string>
#include <iostream>

int main() {
    boost::fusion::tuple<int, float, std::string, long> ip{127, 0.0, "0", 1};
    boost::fusion::for_each(ip, [](auto i) { std::cout << i << std::endl; });

    return 0;
}
