// Итератор (Iterator)

#include <iostream>
#include <set>
#include <numeric>
#include <array>
#include <iterator>

template<class _Tp, size_t _Size>
class quad
{
public:
    auto begin()
    {
        return flat_iterator{*this, 0};
    }
    auto end()
    {
        return flat_iterator{*this, _Size};
    }
private:
    std::array<std::array<_Tp, _Size>, _Size> m;

    class flat_iterator {
    public:
        flat_iterator(quad& o, std::size_t i)
                :o{o}, i{i}, j{0}
        {
        };

        bool operator!=(const flat_iterator& it)
        {
            return i!=it.i || j!=it.j;
        }

        void operator++()
        {
            if (++j>=_Size) {
                j=0;
                ++i;
            }
        }

        _Tp& operator*()
        {
            return o.m[i][j];
        }

    private:
        quad& o;
        std::size_t i;
        std::size_t j;
    };
};

int main(int, char* [])
{
    // std algorithm
    quad<int, 3> q{};
    std::iota(std::begin(q), std::end(q), 42);

    // for
    for (const auto& i: q) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // tree
    std::set<int> tree{std::begin(q), std::end(q)};
    for (const auto& i: tree) {
        std::cout << i << std::endl;
    }

    // filesystem
    // sql
    // ...

    return 0;
}
