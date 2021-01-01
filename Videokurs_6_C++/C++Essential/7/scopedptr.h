#pragma once

// boost: scoped_ptr

template <typename T>
class ScopedPtr
{
public:
    explicit ScopedPtr(T* ptr);
    ~ScopedPtr();
    T& operator*();
    T* operator->();

private:
    T* ptr;
};
