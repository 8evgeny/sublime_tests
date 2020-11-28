// unordered_multimap
#include <iostream>
#include <unordered_map>

int main() {
    std::unordered_multimap<std::string, std::string> umm{{"one", "один"},
                                                         {"one", "раз"},
                                                         {"two", "два"}};
    for (const auto &[en, ru]: umm) {
        std::cout << en << " <=> " << ru << std::endl;
    }
}
