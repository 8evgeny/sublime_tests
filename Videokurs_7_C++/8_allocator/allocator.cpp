#include <iostream>
#include <vector>
#include <map>
#include <tuple>


template<typename T>
struct logging_allocator {
    using value_type = T;
/*    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template<typename U>
    struct rebind {
        using other = logging_allocator<U>;
    };*/

    T *allocate(std::size_t n) const {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        auto p = std::malloc(n * sizeof(T));
        if (!p)
            throw std::bad_alloc();
        return reinterpret_cast<T *>(p);
    }

    void deallocate(T *p, std::size_t n) const {
        std::cout << __PRETTY_FUNCTION__ << "[n = " << n << "]" << std::endl;
        std::free(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) const {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        new(p) U(std::forward<Args>(args)...);
    };

    void destroy(T *p) const {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        p->~T();
    }
};

int main(int, char *[]) {

    auto v = std::vector<int, logging_allocator<int>>{};
//    v.reserve(5);
    for (size_t i = 0; i < 1 /* 5 */; ++i) {
        v.emplace_back(i);
        std::cout << "---" << std::endl;
    }

    for (auto i: v) {
        std::cout << i << std::endl;
    }

//    auto m = std::map<int, int, std::less<int>, logging_allocator<std::pair<const int, int>>>{};
//    for (size_t i = 0; i < 5; ++i) {
//        m.emplace(i, i);
//        std::cout << "---" << std::endl;
//    }

//    auto h = std::map<int, hard, std::less<int>, logging_allocator<std::pair<const int, hard>>>{};
//    for (size_t i = 0; i < 5; ++i) {
//        h.emplace(i, hard(i, i));
//        std::cout << std::endl;
//    }

    return 0;
}

/*
struct hard {
    int i;
    double d;

    hard(int i, double d) : i(i), d(d) { std::cout << __PRETTY_FUNCTION__ << std::endl; };

    hard(const hard &)
    = delete;
//    { std::cout << __PRETTY_FUNCTION__ << std::endl; };

    hard(hard &&) noexcept
    = delete;
//    { std::cout << __PRETTY_FUNCTION__ << std::endl; };

    ~hard() { std::cout << __PRETTY_FUNCTION__ << std::endl; };
};
*/























/*
h.emplace(std::piecewise_construct, std::forward_as_tuple(i), std::forward_as_tuple(i, i));
*/
