#include <iostream>


template<typename... Args>
void iterate1(Args... args) {
    printf("iterate1 = %s\nsizeof = %lu\nargs = %d %f %s\n", __PRETTY_FUNCTION__, sizeof...(args), args ...);
}

void iterate2() {
    std::cout << std::endl;
}

template<typename T, typename... Args>
void iterate2(T t, Args... args) {
    std::cout << t << " ";
    iterate2(args...);
}

template<typename... Args>
void iterate3(Args... args) {
    // int a[3] = {(std::cout << 1, 0), (std::cout << 2.0, 0), (std::cout << "tri", 0)};
    int a[sizeof...(args)] = {(std::cout << "???" << args << ", ", 0)...};

    std::cout << std::endl;
}

int main(int, char *[]) {
    std::cout << "\n\n=====" << std::endl;

    // iterate1(1, 2.0, "tri");
    // iterate2(1, 2.0, "tri");
    iterate3(1, 2.0, "tri");

    return 0;
}
