#include <iostream>

auto a{0};

auto foo() {
    return a += 2;
}

auto bar() {
    return a *= 2;
}

auto baz(int a, int b) {
    std::cout << a << " " << b << std::endl;
    return a + b;
}

int main() {
    a = 1;
    std::cout << foo() << bar() << std::endl; // evaluation order guaranteed
    a = 1;
    std::cout << baz(foo(), bar()) << std::endl; // evaluation order undefined

    return 0;
}
