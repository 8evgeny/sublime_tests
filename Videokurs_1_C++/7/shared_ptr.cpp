#include <iostream>
#include <utility>
#include <stdio.h>

class xray {
public:
    xray() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    };

    xray(const xray &) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    };

    xray(int, int) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    ~xray() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    };
};

template<typename T>
class smart_ptr {
    T *ptr;
    int counter;
public:
    smart_ptr(T *p) : ptr{p}, counter{1} {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    smart_ptr(const smart_ptr &u) : ptr{u.ptr}, counter{u.counter} {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        ++counter;
    }

    smart_ptr(smart_ptr &&u) : ptr{u.ptr}, counter{u.counter} {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    auto get() {
        return ptr;
    }

    auto use_count() {
        return counter;
    }

    ~smart_ptr() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if (--counter == 0) {
            delete ptr;
        }
    }
};

int main() {
//    auto p1 = smart_ptr<xray>{new xray{1, 2}};
//    std::cout << p1.use_count() << std::endl;
//    auto p2 = p1;
//    std::cout << p1.use_count() << p2.use_count() << std::endl;
//    auto p3 = std::move(p1);
//    std::cout << p2.use_count() << p3.use_count() << std::endl;

//    auto s1 = std::shared_ptr<FILE>{fopen("/dev/null", "w")};
//    std::cout << sizeof(s1) << std::endl;

//    auto u2 = std::shared_ptr<FILE>{fopen("/dev/null", "w"), fclose};
//    std::cout << sizeof(u2) << std::endl;

//    auto u3 = std::make_shared<std::string>("hello", 5);
}
