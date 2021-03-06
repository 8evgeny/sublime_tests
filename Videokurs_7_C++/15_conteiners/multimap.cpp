 // multimap
#include <iostream>
#include <map>

int main()
{
    std::multimap<int, int> x{{1, 1}, {1, 2}, {2, 1}};
    for(auto [i, j]: x)
    {
        std::cout << i << j << std::endl;
    }
}
