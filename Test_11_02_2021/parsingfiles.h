#pragma once
#include <memory>
#include <experimental/propagate_const>
#include <boost/filesystem/operations.hpp>
template <class T>
using Pimpl = std::experimental::propagate_const<std::unique_ptr<T>>;

class ParsingFiles
{
public:
    ParsingFiles(std::string);

private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;;
};


