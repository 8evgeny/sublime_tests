#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>

int main() {
    std::vector<int> v{0, 1, 2, 3, 4, 5};
    std::vector<int> d(5);
    std::copy_if(v.begin(), v.end(), d.begin(), [](auto i){return i > 2;});
    for (auto i : d) std::cout << i << " ";
    std::cout << std::endl;

    // std::back_inserter => push_back
    // std::front_inserter => push_front
    // std::inserter => insert
    std::copy(v.begin(), v.end(), std::back_inserter(d));
    for (auto i : d) std::cout << i << " ";
    std::cout << std::endl;

    std::copy_n(v.begin(), 2, std::back_inserter(d));
    for (auto i : d) std::cout << i << " ";
    std::cout << std::endl;
}
