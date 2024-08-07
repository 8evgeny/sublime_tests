#pragma once

#include <boost/program_options.hpp>
#include <chrono>
#include <experimental/propagate_const>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <thread>
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

class Compare_Node {
 public:
  bool operator()(const Node* l, const Node* r) const {
    return l->num_in_node < r->num_in_node;
  };
};

class Coding {
 public:
  Coding();
  ~Coding();
  struct Impl;

 private:
  std::unique_ptr<Impl> _d;
};

class Decoding {
 public:
  Decoding();
  ~Decoding();
  struct Impl;

 private:
  std::unique_ptr<Impl> _d;
};
