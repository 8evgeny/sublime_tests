#pragma once
#include <experimental/propagate_const>
#include <iostream>
#include <memory>
template <class T>
using Pimpl = std::experimental::propagate_const<std::unique_ptr<T>>;
#include <mutex>
class ParsingFiles {
 public:
  //    ParsingFiles(std::string);
  ParsingFiles();
  ~ParsingFiles();
  void ParsingDir(std::string, std::string);
  struct Impl;

 private:
  std::unique_ptr<Impl> _d;
};
