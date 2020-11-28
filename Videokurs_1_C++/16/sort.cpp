#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v{3, 2, 1, 5, 4, 3, 6, 5, 4, 7, 6, 5};

    std::sort(v.begin(), v.end(), std::greater<>{});
    for (auto i : v) std::cout << i << " ";
    std::cout << std::endl;

    std::stable_sort(v.begin(), v.end(), std::greater<>{});
    for (auto i : v) std::cout << i << " ";
    std::cout << std::endl;

    v = {3, 2, 1, 5, 4, 3, 6, 5, 4, 7, 6, 5};
    std::partial_sort(v.begin(), v.begin() + 6, v.end());
    for (auto i : v) std::cout << i << " ";
    std::cout << std::endl;

    std::cout << std::is_sorted(v.begin(), v.end()) << std::endl;
    auto su = std::is_sorted_until(v.begin(), v.end());
    for(auto i = v.begin(); i != su; ++i) std::cout << *i << " ";
    std::cout << std::endl;

    v = {3, 2, 1, 5, 4, 3, 6, 5, 4, 7, 6, 5};
    std::nth_element(v.begin(), v.begin() + 6, v.end());
    std::cout << "nth_element = ";
    for (auto i : v) std::cout << i << " ";
    std::cout << std::endl;

    std::sort(v.begin(), v.end());
    for (auto i : v) std::cout << i << " ";
    std::cout << std::endl;

    auto af = std::adjacent_find(v.begin(), v.end());
    for(auto i = af; i != v.end(); ++i) std::cout << *i << " ";
    std::cout << std::endl;

    v.erase(std::unique(v.begin(), v.end()), v.end());
    for (int i : v) std::cout << i << " ";
    std::cout << std::endl;

//    merge // merges two sorted ranges
//    inplace_merge
}
