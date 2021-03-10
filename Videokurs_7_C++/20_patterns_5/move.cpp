#include <chrono>
#include <condition_variable>
#include <iostream>
#include <queue>
#include <thread>

struct xray {
    xray() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

    xray(const xray&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }

    xray(xray&&) noexcept { std::cout << __PRETTY_FUNCTION__ << std::endl; }

    xray(const char*) { std::cout << __PRETTY_FUNCTION__ << std::endl; }

    ~xray() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

std::ostream& operator<<(std::ostream & o, const xray &)
{
    o << "xray";
    return o;
}

//using T = std::string;
using T = xray;

using args = std::tuple<T, T>;

void foo(const T& a, const T& b)
{
    std::cout << a << " " << b << std::endl;
}

int main()
{
    std::queue<args> msgs;
    msgs.emplace("hello", "en");

    // move or copy?
//    auto [a, b] = msgs.front();
//    foo(a, b);
//    std::invoke(foo, a, b);

//    auto c = std::move(msgs.front());
//    std::apply(foo, c);

//    std::apply(foo, msgs.front());

    return 0;
}
