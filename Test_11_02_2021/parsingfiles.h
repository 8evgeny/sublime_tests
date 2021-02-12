#pragma once
#include <memory>
#include <experimental/propagate_const>
#include <boost/filesystem/operations.hpp>
#include <iostream>
template <class T>
using Pimpl = std::experimental::propagate_const<std::unique_ptr<T>>;

class ParsingFiles  {
public:
//    ParsingFiles(std::string);
  ParsingFiles();
  ~ParsingFiles();
  void ReadDir();
  struct Impl;


private:
  std::unique_ptr<Impl> _d;
};


