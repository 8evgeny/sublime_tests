#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <mutex>
#include <string>
#include <tuple>
#include <vector>


template<typename T>
struct foo {
    foo(T v) : m_value{v} {}

    T getValue() const { return m_value; }

private:
    T m_value;
};

template<typename T>
struct bar {
    bar(T value) : m_valuePtr{std::make_unique<T>(value)} {};

    T getValue() const { return *m_valuePtr; }

private:
    std::unique_ptr<T> m_valuePtr;
};


template<typename T>
struct Buffer {

    Buffer() = default;

    Buffer(const std::initializer_list<T> &list) : m_buffer{list} {}

    template<typename Iterator>
    Buffer(Iterator begin, Iterator end) : m_buffer{begin, end} {};

    template<typename P, typename U>
    Buffer(P *, U *) {};

    void print() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        for (const auto &v : m_buffer) {
            std::cout << v << ' ';
        }
        std::cout << std::endl;
    }

private:
    std::vector<T> m_buffer;
};

template<typename Iter>
Buffer(Iter begin, Iter end) -> Buffer<typename std::iterator_traits<Iter>::value_type>;

template<typename P, typename U>
Buffer(P *, U *) -> Buffer<P>;

template<typename T>
void zoo(T t) {
    std::cout << t << std::endl;
}

int main() {
    zoo<int>(3);
    zoo(3.14);

    foo a(10.12);
    std::cout << "a.value = " << a.getValue() << std::endl;
    bar b{10};
    std::cout << "b.value = " << b.getValue() << std::endl;

    Buffer buffer{0, 1, 2, 3, 4, 5, 6};
    buffer.print();

    Buffer buffer2 = buffer;
    buffer2.print();

    std::vector<int> values = {6, 5, 4, 3, 2, 1, 0};

    Buffer buffer3(values.cbegin(), values.cend());
    buffer3.print();

    char *c = nullptr;
    int *i = nullptr;
    Buffer bb(c, i);

    return 0;
}
