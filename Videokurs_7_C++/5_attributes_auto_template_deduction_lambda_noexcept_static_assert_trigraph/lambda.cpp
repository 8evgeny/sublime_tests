#include <array>

int main() {
    int a;
    static_assert([](auto i){return i;}(42));

    static_assert([](auto i) constexpr -> int {return i;}(42));

    auto getSize = [](){ int a = 0; return 42; };
    std::array<int, getSize()> arr{};

    auto getSizeStatic = [](){ static int a = 0; return 42;};
//    std::array<int, getSizeStatic()> arr2{};

    return 0;
}
