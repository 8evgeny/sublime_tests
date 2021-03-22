#pragma once;
#include <string>
using namespace std;
class planets {
 public:
  planets();

  //  struct data {
  double lon{0};
  int house{0};
  double speed{0};
  double distance{0};
  bool retro;
  int nakshatra{0};
  //  };
};
class Su : public planets {};
class Ch : public planets {};
class Ma : public planets {};
class Bu : public planets {};
class Gu : public planets {};
class Sk : public planets {};
class Sa : public planets {};
class Ra : public planets {};
class Ke : public planets {};
class As : public planets {};

struct nativ {
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

  string bighday = "17-11-1966";
  string btime = "01:50:00";
  string lon = "35.14";  // my
  string lat = "47.84";  // my
};
