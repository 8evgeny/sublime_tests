// array
#include <iostream>
#include <array>

/*

 */

int main() {
    std::array<int, 10> x;//{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (auto i: x) {
        std::cout << i << std::endl;
    }
    std::cout << ".max_size() = " << x.max_size() << std::endl;

    std::cout << "sizeof(x) = " << sizeof(x) << std::endl;

    auto[a, b, c, d, e, f, g, h, i, j] = x;

    std::cout << j << std::endl;

    std::array<int, 2> a1{1, 2};
    std::array<int, 2> a2{2, 1};

    std::cout << "(a1 > a2) is " << (a1 > a2) << std::endl;
    std::cout << "(a1 < a2) is " << (a1 < a2) << std::endl;

    std::cout << x.at(10) << std::endl;
}
