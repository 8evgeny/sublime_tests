#pragma once

#include <iostream>

struct xray {
    std::string x;

    xray(const char *x_) : x(x_)
    {
        std::cout << "ctor " << x << std::endl;
    }

    xray(const xray &rhs) : x(rhs.x)
    {
        std::cout << "copy ctor from " << rhs.x << " to " << x << std::endl;
    }

#ifdef MOVE

    xray(xray &&rhs) noexcept
    {
        std::cout << "move ctor from " << rhs.x << " to " << x << std::endl;
        x.swap(rhs.x);
    }

#endif

    ~xray()
    {
        std::cout << "dtor " << x << std::endl;
    }
    xray &operator=(const xray &rhs)
    {
        std::cout << "copy assign from " << rhs.x << " to " << x << std::endl;
        return *this;
    }

#ifdef MOVE

    xray &operator=(xray &&rhs) noexcept

    {
        std::cout << "move assign from " << rhs.x << " to " << x << std::endl;
        return *this;
    }

#endif
};
