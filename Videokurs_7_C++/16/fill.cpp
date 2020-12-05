#include <iostream>
#include <numeric>
#include <vector>

struct fibonacci {
    int a = 0;
    int b = 1;

    int operator()() {
        auto t = a;
        a = b;
        b += t;
        return t;
    }
};

int main() {
    std::vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // *_n количество, вместо диапазона
    // заполнение значением
    std::fill_n(v.begin(), 5, 0);
    for (auto i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::fill(v.begin(), v.end(), 1);
    for (auto i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // заполнение последовательностью
    std::iota(v.begin(), v.end(), -1);
    for (auto i : v) std::cout << i << " ";
    std::cout << std::endl;

    // заполнение произвольным значением
    std::generate_n(v.begin(), 5, fibonacci{});
    for (auto i : v) std::cout << i << " ";
    std::cout << std::endl;

    std::generate(v.begin(), v.end(), fibonacci{});
    for (auto i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
