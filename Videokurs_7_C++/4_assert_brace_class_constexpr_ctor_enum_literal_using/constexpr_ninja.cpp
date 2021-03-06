#include <iostream>

// https://godbolt.org/ gcc 9.2 -O1
//const
int a[] = {1, 2, 3};
auto foo() {
//    const
//    int a[] = {1, 2, 3};
    return a[1];
}

// constexpr
auto fibonacci_naive(long long n) {
    if (n <= 1)
        return n;
    else
        return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

// constexpr
auto factorial_naive(long long n) {
    if (n <= 1)
        return n;
    else
        return n * factorial_naive(n - 1);
}

template<long long N>
struct factorial {
    static const long long value = N * factorial<N - 1>::value;
};

template<>
struct factorial<1> {
    static const long long value = 1;
};

int main() {
    // 41 выполняется 0.9s
    // 42 выполняется 1.4s
    // 50 уже около минуты
    // больше 92 не влезет в 63 бита (signed)
    // больше 93 не влезет в 64 бита (unsigned)
    std::cout << fibonacci_naive(50) << std::endl;
    std::cout << factorial<18>::value << std::endl; // больше 20 не влезет в 64 бита
    std::cout << factorial_naive(18) << std::endl; // больше 20 не влезет в 64 бита
}
