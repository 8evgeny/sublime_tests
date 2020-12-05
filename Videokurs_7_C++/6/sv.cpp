#include <iostream>

using namespace std::string_literals;
using namespace std::string_view_literals;

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Hello, World!"s << std::endl;
    std::cout << "Hello, World!"sv << std::endl;

    auto hw = "Hello, World!"s;
    std::string_view w = hw;
    w = w.substr(7, 5);

    std::cout << w << std::endl;

    std::cout << hw.data() << std::endl;
    std::cout << w.data() << std::endl;

    std::cout << (void *)hw.data() << std::endl;
    std::cout << (void *)w.data() << std::endl;
}
