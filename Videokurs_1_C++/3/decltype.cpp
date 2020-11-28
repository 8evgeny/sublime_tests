#include <iostream>
#include <vector>

// typeid(type | expr), sizeof(type | expr), noexcept(expr), and decltype(expr)

auto fa = 1 + 3.14 + 65;
decltype(1 + 3.14) f = 1 + 3.14;

// decltype(x * x) bar(int x)
auto bar(int x) -> decltype(x * x)
{
    return x * x;
}

int i = 42;

auto foo()
{
    const int &y = i;
    return y;
}

int main(int, char *[])
{
	auto j = foo();
	j = 1;

    std::cout << i << std::endl;
    std::cout << j << std::endl;
    std::cout << typeid(j).name() << std::endl;

	return 0;
}

struct car {
    int engine;
private:
    car() = delete;
};
decltype(car::engine) c1; // car()

auto ex()
{
    throw std::runtime_error("fatal");
    return 42;
}
decltype(ex()) c2;

int arr[10];

decltype(arr[1000]) c3 = i;

auto f1 = decltype(1 + 3.14)(1);
