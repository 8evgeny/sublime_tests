 // set
#include <iostream>
#include <set>

int main()
{
    std::set<int> x{6, 7, 4, 8, 3, 8};
    std::set<int> y{3, 2, 1, 6, 5, 4};
    x.merge(y);
    for(auto i: x)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << x.count(6) << " ";
}
