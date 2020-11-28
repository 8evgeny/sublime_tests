#include <iostream>

using namespace std::string_literals;

std::string operator""_kg(unsigned long long)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return "sorok dva";
}

std::string operator""_rate(long double)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return "sorok dva";
}

std::string operator""_english(const char *, size_t)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return "sorok dva";
}

int main(int, char *[]) {
    auto a = 42_kg;
    std::cout << a << std::endl;

    auto b = 42.0_rate;
    std::cout << b << std::endl;

    auto c = "42"_english;
    std::cout << c << std::endl;

    auto d = "hello world"; // s
    std::cout << d << std::endl;
    std::cout << typeid(d).name() << std::endl;

    return 0;
}
