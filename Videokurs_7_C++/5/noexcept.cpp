#include <iostream>

class foo {
public:
    void over() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    void over() const {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    void dang() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
//    void dang() noexcept {
    void safe() noexcept(true) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

void dang() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void safe() noexcept {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main() {
//    const
    foo f;
    f.over();

    f.dang();
    f.safe();

    void (*fp)() noexcept;
//    fp = dang;
    fp = safe;
}
