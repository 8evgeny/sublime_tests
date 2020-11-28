 // list
#include <iostream>
#include <list>

int main()
{
    std::list<int> x{1, 2, 3, 4, 5};
    for(auto i = x.rbegin(); i != x.rend(); ++i)
    {
        std::cout << *i << std::endl;
    }
}
