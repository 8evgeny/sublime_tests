// deque
#include <iostream>
#include <deque>

#include "xray.h"

int main() {
    // через два указателя
    std::deque<int> v; // std::vector<std::vector<int>>
    for (auto i: v) {
        std::cout << i << std::endl;
    }

    v = {3, 2, 1, 0, -1, -2, -3};
    v.pop_front();
    v.emplace_front(4);
    // vs?
    v.push_front(5);
    for (auto i: v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;


    // один чанк не меньше 16 элементов и не менее 4k суммарно
    std::deque<xray::object, xray::allocator<xray::object>> xray;
    for (auto i = 0u; i < 17; ++i) {
        xray.emplace_back(i);
        std::cout << "---" << std::endl;
    }

    std::cout << "===" << std::endl;

    xray.emplace_front(100);
    std::cout << "---" << std::endl;

    xray.emplace_front(101);
    std::cout << "===" << std::endl;

    auto i = xray.begin();
    std::advance(i, 10);
    xray.emplace(i, 200);
    std::cout << "---" << std::endl;
    xray.emplace(i, 201);
    std::cout << "===" << std::endl;

    for(const auto &i: xray)
    {
        std::cout << i.value() << " ";
    }
    std::cout << std::endl;
}
