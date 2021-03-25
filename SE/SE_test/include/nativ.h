#pragma once
#include <iostream>
#include <string>
#include <tuple>

#include "main.h"
using namespace std;
namespace po = boost::program_options;
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

class nativ {
 public:
  nativ(string);
  nativ();  //для текущего времени
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

  bool print_calc;
  void readConfig(const char*, po::variables_map&, string);
  pair<string, string> datetimenow();
  void printAll();
  int calc();
  int print_line(int mode, AS_BOOL is_first, int sid_mode);

  string what_vara(string, string);
  float what_tithi();
  float what_naksh();
  string what_karana();
  float what_yoga();
  void panchang();

  string path;
  string name;
  string bday;
  string btime;
  string lon;
  string lat;
  string city;

  float tithi{0};
  string karana;
  string vara;
  float naksh{0};
  float yoga{0};
};

class muhurta{
public:
    muhurta();
    muhurta(nativ&);

};