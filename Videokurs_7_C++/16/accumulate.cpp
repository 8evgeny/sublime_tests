#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> v{2, 3};

    auto sum = std::accumulate(v.begin(), v.end(), 1);
    std::cout << sum << std::endl;

    auto op = [](auto a, auto b) {
        return "op(" + std::move(a) + ", " + std::to_string(b) + ")";
    };

    auto reverse_engineering = std::accumulate(v.begin(), v.end(), std::string("init"), op);

    std::cout << reverse_engineering << std::endl;

    reverse_engineering = std::reduce(v.begin(), v.end(), std::string("init"), op);
    std::cout << reverse_engineering << std::endl;
}
