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
  void printAll(nativ&);
  int calc();
  int print_line(int mode, AS_BOOL is_first, int sid_mode);

  //  string findVaraString(string, string);
  tuple<string, int, string> findVarafromTm(struct tm&);
  tuple<double, string, string, string, string> findTithi(nativ&);
  pair<string, string> findStartTithi(nativ&, int);
  pair<string, string> findEndTithi(nativ&, int);
  tuple<double, string, string, string> find_naksh(nativ&);
  string find_karana(nativ&);
  float find_yoga(nativ&);
  void panchang(nativ&);
  void panchangPrint(nativ&);
  struct tm fromStringToTm(string, string);
  pair<string, string> fromTmToString(struct tm&);
  chrono::system_clock::time_point fromStringToCrono(string, string);
  pair<string, string> fromCronoToString(chrono::system_clock::time_point);
  tm fromCronoToTm(chrono::system_clock::time_point);
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
  string tithiGod;
  string tithiResult;
  string karana;
  int vara{0};
  string varaName;
  string varaLord;
  float naksh{0};
  string nakshName;
  string nakshLord;
  string nakshGod;
  float yoga{0};
  string yogaName;
};

class muhurta {
 public:
  muhurta();
  muhurta(nativ&);
};
