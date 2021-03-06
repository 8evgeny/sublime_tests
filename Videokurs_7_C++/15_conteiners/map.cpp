 // map
#include <iostream>
#include <map>

int main()
{
    // если не set
    // - operator <
    // - новый объект
    std::map<int, int> x;

    auto f = x.find(0);
    if (f == x.end())
    {
        x[0] = 1;
    }

    // только новый
    auto [a, b] = x.insert({1, 2});
    // только новый, зачем?
    auto [a1, b1] = x.try_emplace(1, 3);
    // новый или перезапишет
    auto [a2, b2] = x.insert_or_assign(1, 4);
    x[1] = 5;
    auto z = x[99];

    for(auto [i, j]: x)
    {
        std::cout << i << ", " << j << std::endl;
    }

    std::cout << x.at(2) << std::endl;
}
