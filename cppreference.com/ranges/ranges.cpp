#include <ranges>
#include <vector>
#include <iostream>
#include <type_traits>

int main()
{
    std::vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for(int n : std::views::all(v) | std::views::take(6) ) {
        std::cout << n << ' ';
    }

    static_assert(std::is_same<
        decltype(std::ranges::views::single(42)),
        std::ranges::single_view<int>
        >{});

    static_assert(std::is_same<
        decltype(std::views::all(v)),
        std::ranges::ref_view<std::vector<int, std::allocator<int>>>
        >{});

    int a[]{1,2,3,4};
    static_assert(std::is_same<
        decltype(std::views::all(a)),
        std::ranges::ref_view<int [4]>
        >{});

    static_assert(std::is_same<
        decltype(std::ranges::subrange{std::begin(a)+1, std::end(a)-1}),
        std::ranges::subrange<int*, int*, std::ranges::subrange_kind(1)>
        >{});
}
