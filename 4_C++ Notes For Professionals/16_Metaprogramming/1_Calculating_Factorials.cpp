#include <iostream>

using namespace std;

template<unsigned int n>
struct factorial
{
    enum
    {
        value = n * factorial<n - 1>::value
    };
};
template<>
struct factorial<0>
{
    enum { value = 1 };
};
int main()
{
    int my_array[factorial<5>::value] = {0};
    int j = 0;
    for (auto i:my_array)
    {
        i = j++;
        std::cout << i <<" ";
    }
    std::cout << "\n";
    std::cout << "factorial<8> = " <<factorial<8>::value << std::endl;
}
