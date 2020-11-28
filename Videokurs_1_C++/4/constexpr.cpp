#include <array>
#include <iostream>

int foo(int i) {
    return i + i;
}

constexpr int bar(int i) {
    return i + i;
}

int main(int, char *[]) {
    auto c = std::array<char, 10>();

    int n = 10;
//    auto d = std::array<char, n>(); // not a constant

    const int m = 10;
    auto e = std::array<char, m>();

    // const vs constexpr

   // auto f = std::array<char, foo(10)>(); // is not a constant
   // auto g = std::array<char, foo(n)>(); // is not a constant
   // auto h = std::array<char, foo(m)>();

    auto f = std::array<char, bar(10)>();
   // auto g = std::array<char, bar(n)>(); // is not a constant
    auto h = std::array<char, bar(m)>();

    int z = bar(10);

    return 0;
}
