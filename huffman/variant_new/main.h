#pragma once
#include <stdlib.h>
#include <time.h> /* time_t, struct tm, difftime, time, mktime */

#include <algorithm>
#include <boost/program_options.hpp>
#include <chrono>
#include <cstdlib>
#include <execution>
#include <experimental/propagate_const>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
namespace po = boost::program_options;
template <class T>
using Pimpl = std::experimental::propagate_const<std::unique_ptr<T>>;

class Node {
 public:
  int num_in_node{0};   // число в узле
  char char_in_node{};  //символ в узле
  Node* left_branch;
  Node* right_branch;

  Node();              // Конструктор для потомков
  Node(Node*, Node*);  // Конструктор для создания родителя
};

class Codding {
 public:
  Codding();
  ~Codding();
  struct Impl;

 private:
  std::unique_ptr<Impl> _d;
};
