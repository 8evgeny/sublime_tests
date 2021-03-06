#include <iostream>
#include <memory>
#include <stdio.h>


auto null_factory() {
    static std::weak_ptr<FILE> cache;
    auto spt = cache.lock();
    if (spt) {
        std::cout << "hit" << std::endl;
    } else {
        std::cout << "miss" << std::endl;
        spt = std::shared_ptr<FILE>{fopen("/dev/null", "w"), &fclose};
        cache = spt;
    }
    return spt;
}

int main() {
    {
        auto n1 = null_factory();
        auto n2 = null_factory();
        std::cout << n1.use_count();
    }

    {
        auto n1 = null_factory();
    }

    {
        auto n2 = null_factory();
    }
}
