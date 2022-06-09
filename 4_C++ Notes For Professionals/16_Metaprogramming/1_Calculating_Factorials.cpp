#include <iostream>
#include <array>

template<unsigned int n>
struct factorial
{
    enum
    {
        val = n * factorial<n - 1>::val
    };
};
template<>
struct factorial<0>
{
    enum { val = 1 };
};

//Еще один способ
#include <type_traits>
template<long long n>
struct factorial_v2 :
                   std::integral_constant<long long, n * factorial_v2<n - 1>::value> {};
template<>
struct factorial_v2<0> :
                      std::integral_constant<long long, 1> {};

//Additionally, constexpr functions become a cleaner alternative.
constexpr long long factorial_v3(long long n)
{
    return (n == 0) ? 1 : n * factorial_v3(n - 1);
}

//Since c++17 one can use fold expression to calculate factorial:
#include <utility>

//template <class T, T N, class I = std::make_integer_sequence<T, N>>
//struct factorial_v4;

//template <class T, T N, T... Is>
//struct factorial_v4<T,N,std::index_sequence<T, Is...>>
//{
//    static constexpr T value = (static_cast<T>(1) * ... * (Is + 1));
//};



int main()
{
    int my_array[factorial<5>::val] = {0};
    int j = 0;
    for (auto i:my_array)
    {
        i = j++;
        std::cout << i <<" ";
    }
    std::cout << "\n";
    std::cout << "factorial<8> = " <<factorial<8>::val << std::endl;

    std::cout << "factorial_v2<7> = " << factorial_v2<7>::value << std::endl;

    std::array<char, factorial_v3(9)> arr;
    std::cout << arr.size ()<< '\n';
    std::cout << factorial_v3(6) << '\n';

//    std::cout << factorial_v4<int, 5>::value << std::endl;
}
