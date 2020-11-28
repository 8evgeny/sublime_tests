// #define MOVE
#include "xray.h"

#include <iostream>

void foo(const xray &)
{
    std::cout << "= const ref" << std::endl;
}

void foo(xray &&)
{
    std::cout << "= temporary" << std::endl;
}

template<class T>
void baz(T &&t)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

template<class T>
void bar(T &&t)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    baz(std::forward<T>(t));
}

int main(int, char *[]) {
    xray x("x");

    // xray x("x");
    // xray y("y");

    // xray x("x");
    // xray y("y");
    // x = y;

    // xray x("x");
    // x = xray("y");

    // xray x("x");
    // foo(x);

    // foo(xray("x"));

    // xray x("x");
    // foo(x); // remove const

    // foo(xray("x"));

    // xray x("x");
    // xray y("y");
    // x = std::move(y);

    // x = xray("y");

    // foo(xray("y"));

    // x = std::move(y);
    // bar(x);
    // bar(xray("tmp"));

    std::cout << "---" << std::endl;

    return 0;
}
