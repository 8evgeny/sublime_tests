// unordered_multiset
#include <iostream>
#include <unordered_set>

#include "xray.h"

int main() {
    std::unordered_multiset<xray::object, std::hash<xray::object>, std::equal_to<>, xray::allocator<xray::object>> ums;
    for (const auto &i: {1, 2, 3, 1}) {
        ums.emplace(i);
        std::cout << "---" << std::endl;
    }
    std::cout << "=== " << ums.bucket_count() << std::endl;
}
