#pragma once
#include <memory>
#include <experimental/propagate_const>

template <class T>
using Pimpl = std::experimental::propagate_const<std::unique_ptr<T>>;

class ParsingFiles
{
public:
    ParsingFiles();

private:
    struct Impl;
    Pimpl<Impl> _d;
};


