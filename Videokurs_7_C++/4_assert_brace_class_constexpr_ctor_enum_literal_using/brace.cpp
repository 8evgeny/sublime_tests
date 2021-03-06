#include <iostream>

struct foo {
    int a = -1;
    int b{-2};
    int c{-3};
};

struct bar {
    bar() = default;
    bar(int a_, int b_) : a(a_ * 10), b(b_ * 10), c(30) {};
//    bar(std::initializer_list<int> il) : a(il.size()), b(0), c(0) {};
    int a{-1};
    int b{-2};
    int c{-3};
};

int main(int, char *[]) {
    int i[4] = {1, 2, 3, 4};
    int j[] = {1, 2, 3, 4};

    foo f{1, 2};

    std::cout << f.a << std::endl;
    std::cout << f.b << std::endl;
    std::cout << f.c << std::endl;

    bar b(1, 2);

    std::cout << b.a << std::endl;
    std::cout << b.b << std::endl;
    std::cout << b.c << std::endl;

    return 0;
}
