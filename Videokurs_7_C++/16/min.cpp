#include <iostream>
#include <vector>

int main() {
    auto a = 1;
    auto b = 2;
    auto c = 3;

    // минимальное значение
    decltype(auto) n = std::min(a, b);
    std::cout << n << std::endl;
    a = -1;
    std::cout << n << std::endl;
    a = 1;

    // максимальное значение
    auto m = std::max({&a, &b, &c});
    std::cout << *m << std::endl;
    *m = -1;
    std::cout << "a=" << a << " b=" << b << " c=" << c << std::endl;

    // пограничные значения
    auto op = [](auto a, auto b) {
        return a < b; // только для добрых дел
    };
    auto [in, ax] = std::minmax({1, 2, 3}, op);
    std::cout << "min=" << in << " max=" << ax << std::endl;

    // тоже самое в контейнерах
    std::vector<int> v{3, 2, 1, 4, 5, 6};
    auto [min_it, max_it] = std::minmax_element(v.begin(), v.end());
    std::cout << "min=" << *min_it << " max=" << *max_it << std::endl;

    min_it = std::min_element(v.begin(), v.end());
    *min_it = 99;
    for(auto i : v) std::cout << i << " "; std::cout << std::endl;

    // оганичитель
    for(auto i : v) std::cout << i << " => " << std::clamp(i, 2, 5) << std::endl;
}
