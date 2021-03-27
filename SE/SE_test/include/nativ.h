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
  pair<string, string> dateTimeNowInString();
  void printAll();
  int calc();
  int print_line(int mode, AS_BOOL is_first, int sid_mode);

  //  string findVaraString(string, string);
  pair<string, int> findVarafromTm(struct tm&);
  float find_tithi();
  pair<string, string> findStartTithi();
  pair<string, string> findEndTithi();
  float find_naksh();
  string find_karana();
  float find_yoga();
  void panchang();
  struct tm fromStringToTm(string, string);
  string fromStringToVaraLord(string);
  pair<string, string> fromTmToString(struct tm&);
  chrono::system_clock::time_point fromStringToCrono(string, string);
  pair<string, string> fromCronoToString(chrono::system_clock::time_point);
  struct tm fromCronoToTm(chrono::system_clock::time_point);
  string path;
  string name;
  string bday;
  string btime;
  chrono::system_clock::time_point chronoBighDateTime;
  struct tm b_time;
  string lon;
  string lat;
  string city;

  float tithi{0};
  string tithiName;
  string tithiLord;
  string karana;
  int vara{0};
  string varaName;
  string varaLord;
  float naksh{0};
  string nakshName;
  string nakshLord;
  float yoga{0};
  string yogaName;
};

class muhurta {
 public:
  muhurta();
  muhurta(nativ&);
};
