 // multiset
#include <iostream>
#include <set>

int main()
{
    // чем отличается хранение от set?
    std::multiset<int> x{6, 7, 4, 8, 3, 8, 8};
    std::multiset<int> y{3, 2, 1, 6, 5, 4, 4};
    x.merge(y);
    for(auto i: x)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << x.count(6) << " ";
}
