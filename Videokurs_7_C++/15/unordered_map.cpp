// unordered_map
#include <iostream>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, std::string> um{{"one", "один"},
                                                    {"one", "раз"},
                                                    {"two", "два"}};
    for (const auto &[en, ru]: um) {
        std::cout << en << " <=> " << ru << std::endl;
    }
}
