// vector
#include <iostream>
#include <vector>

template<typename...T>
auto make_vector(T...t) {
    std::vector v = {t...};

    for (auto i: v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
};

int main() {
    make_vector(1, 2, 3);

    // через указатель
    auto x = std::vector{1, 2, 3, 4, 5};
    for (auto i: x) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    auto v = x;

    v.assign(3, 5);
    for (auto i: v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    v.reserve(100);
    v.resize(50);
    v.clear();
    std::cout << v.capacity() << std::endl;
    std::cout << v.size() << std::endl;
    std::cout << v.max_size() << std::endl;
    auto e = v.empty(); // v.size() == 0

    v.shrink_to_fit(); // move?

    v = {3, 2, 1, 0, 0, -1, -2, -3}; // 0, 0
    for (auto i = v.begin(); i != v.end(); ) {
        if (*i == 0) {
            i = v.erase(i);
        } else {
            ++i;
        }
    }
    for (auto i: v) {
        std::cout << i << " ";
    }
}
