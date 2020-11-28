#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

bool cmp(int i) {
    return i > 2;
}

bool comp(int i, int p) {
    return i > p;
}

bool comp_helper(int i) {
    return comp(i, 2);
}

int main()
{
    std::vector<int> v{0, 1, 2, 3, 4};

    auto result = std::find_if(std::begin(v), std::end(v), [](auto i){ return i > 2; });
//    auto result = std::find_if(std::begin(v), std::end(v), [p = 2](auto i){ return i > p; });
//    auto result = std::find_if(std::begin(v), std::end(v), cmp);
//    auto result = std::find_if(std::begin(v), std::end(v), comp);
//    auto result = std::find_if(std::begin(v), std::end(v), std::bind(comp, std::placeholders::_1, 2));

    for (; result != std::end(v); ++result)
    {
        std::cout << *result << " ";
    }
    std::cout << std::endl;
}
