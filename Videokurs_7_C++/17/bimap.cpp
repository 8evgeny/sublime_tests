// Bimap

#include <iostream>
#include <string>

#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>

int main() {
    boost::bimap<
            std::string,
            boost::bimaps::multiset_of<std::string>
    > alias;

    alias.insert({"СП", "Санкт-Петербург"});
    alias.insert({"Питер", "Санкт-Петербург"});
    alias.insert({"Нижний", "Нижний Новгород"});

    for (auto i: alias) {
        std::cout << i.right << " известен как " << i.left << std::endl;
    }
    std::cout << std::endl;

    auto i = alias.left.find("Нижний");
    std::cout << i->first << " => " << i->second << std::endl;

    auto j = alias.right.equal_range("Санкт-Петербург");
    for (auto k = j.first; k != j.second; ++k) {
        std::cout << k->first << " => " << k->second << std::endl;
    }

    return 0;
}
