#pragma once;
#include <iostream>
#include <string>
using namespace std;
class planet {
 public:
  planet();
  //  struct data {
  double lon{0};
  int house{0};
  double speed{0};
  double distance{0};
  bool retro;
  int nakshatra{0};
  //  };
};
class Su : public planet {};
class Ch : public planet {};
class Ma : public planet {};
class Bu : public planet {};
class Gu : public planet {};
class Sk : public planet {};
class Sa : public planet {};
class Ra : public planet {};
class Ke : public planet {};
class As : public planet {};

struct nativ {
  nativ(string nn) { name = nn; };
  Su su;
  Ch ch;
  Ma ma;
  Bu bu;
  Gu gu;
  Sk sk;
  Sa sa;
  Ra ra;
  Ke ke;
  As as;
  string name;
  string bday = "";
  string btime = "";
  string lon = "";
  string lat = "";
};
