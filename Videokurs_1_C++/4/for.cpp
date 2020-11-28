#include <array>
#include <iostream>
#include <map>
#include <vector>


int main(int, char *[]) {
    int a[10];
    for(auto i: a)
    {
        std::cout << i << std::endl;
    }

    std::vector<int> v;
    {
        auto begin = v.begin();
        auto end = v.end();
        for(; begin != end; ++begin)
        {
            int i = *begin;
            std::cout << i << std::endl;
        }
    }

    std::string s{"hello"};
    for(auto c: s)
    {
        std::cout << c << std::endl;
    }

    std::map<int, std::string> m{{1, "1"}};
    for(auto c: m)
    {
//        std::cout << c << std::endl;
    }

    return 0;
}
