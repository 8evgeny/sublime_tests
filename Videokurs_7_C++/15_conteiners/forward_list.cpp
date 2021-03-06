 // forward_list
#include <iostream>
#include <forward_list>

int main()
{
    std::forward_list<int> x{2, 1, 4, 3, 5};
    x.sort();
    for(auto i: x)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::forward_list<int> y{2, 1, 4, 3, 5};
//    y.sort();

    x.merge(y);
    for(auto i: x)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    x.unique();
    for(auto i: x)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    x.remove(5);
    x.reverse();
    for(auto i: x)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    x = {2, 1, 4, 3, 5};
    y = {2, 1, 4, 3, 5};

    // 2 -> 1 -> 4
    // 2 -> 4

    x.splice_after(x.before_begin(), y);
    for(auto i: y)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
