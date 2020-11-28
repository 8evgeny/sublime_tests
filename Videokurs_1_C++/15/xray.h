#pragma once

#include <array>

namespace xray {

    class object {
    public:
        object() : object(-1) {
        }

        object(int n) {
            this->n.fill(n);
        }

        object(const object &o) {
            std::cout << this << " copy(" << &o << ");" << std::endl;
            this->n.fill(o.value());
        }

        object(object &&o) noexcept {
            std::cout << this << " move(" << &o << ");" << std::endl;
            this->n.fill(o.value());
        }

        object &operator=(const object &o) {
            std::cout << this << " copy(" << &o << ");" << std::endl;
            this->n.fill(o.value());
            return *this;
        }

        object &operator=(object &&o) noexcept {
            std::cout << this << " move(" << &o << ");" << std::endl;
            this->n.fill(o.value());
            return *this;
        }

        bool operator==(const object &o) const {
            std::cout << this << " compare(" << &o << ");" << std::endl;
            return value() == o.value();
        }

        [[nodiscard]] int value() const {
            return n[0];
        }

    private:
        std::array<int, 0x40> n;
    };

    std::ostream &operator<<(std::ostream &o, const xray::object &x) {
        return o << "xray(" << x.value() << ")";
    }

    template<typename T>
    class allocator {
    public:
        using value_type = T;

        T *allocate(std::size_t n) {
            T *p = reinterpret_cast<T *>(std::malloc(n * sizeof(T)));
            std::cout << p << " allocate(" << n << "); // " << n << " * " << sizeof(T) << " = " << n * sizeof(T)
                      << " bytes" << std::endl;
            return p;
        }

        template<typename U, typename... Args>
        void construct(U *p, Args &&... args) {
            ((std::cout << p << " construct(p, ") << ... << args) << ");" << std::endl;
            ::new(p)U(std::forward<Args>(args)...);
        }

        template<typename U>
        void destroy(U *p) {
            std::cout << p << " destroy(p);" << std::endl;
            p->~U();
        }

        void deallocate(T *p, std::size_t n) {
            std::cout << p << " deallocate(p, " << n << "); // deallocate " << n << " * " << sizeof(T) << " = "
                      << n * sizeof(T) << " bytes" << std::endl;
            std::free(p);
        }

    private:
    };
}

template<>
class std::hash<xray::object> {
public:
    size_t operator()(const xray::object &xo) const {
        std::cout << &xo << " hash();" << std::endl;
        return xo.value();
    }
};
