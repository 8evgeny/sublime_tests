#pragma once
#include <QtWidgets>
#include <iostream>
#include <string>
#include <tuple>

#include "main.h"
#include "sweodef.h"
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
  nativ(int);  //для текущего времени
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
  mutex mtx;
  bool print_calc;
  void readConfig(const char*, po::variables_map&, string);
  pair<string, string> dateTimeNowInString(int);
  void printAll(nativ&);
  int calc();
  int print_line(int mode, AS_BOOL is_first, int sid_mode);

  //  string findVaraString(string, string);
  tuple<string, int, string> findVarafromTm(struct tm&);
  tuple<double, string, string, string, string> findTithi(nativ&);
  pair<string, string> findStartTithi(nativ&, int);
  pair<string, string> findEndTithi(nativ&, int);
  pair<string, string> findStartNaksh(nativ&, int);
  pair<string, string> findEndNaksh(nativ&, int);
  pair<string, string> findStartKarana(nativ&);
  pair<string, string> findEndKarana(nativ&);
  tuple<double, string, string, string, string> findNaksh(nativ&);
  tuple<int, string, string, string, string> findKarana(nativ&);
  float find_yoga(nativ&);
  void panchang(nativ&);
  string navatara(nativ&);
  void panchangPrint(nativ&);
  struct tm fromStringToTm(string, string);
  pair<string, string> fromTmToString(struct tm&);
  chrono::system_clock::time_point fromStringToCrono(string, string);
  pair<string, string> fromCronoToString(chrono::system_clock::time_point);
  pair<string, string> fromCronoToStringlocal(chrono::system_clock::time_point);
  tm fromCronoToTm(chrono::system_clock::time_point);
  tm fromCronoToTmLocal(chrono::system_clock::time_point);
  void qtPanchang(nativ&, string);
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
  chrono::system_clock::time_point tithiStart;
  chrono::system_clock::time_point tithiEnd;
  string tithiName;
  string tithiLord;
  string tithiGod;
  string tithiResult;
  int karana{0};
  chrono::system_clock::time_point karanaStart;
  chrono::system_clock::time_point karanaEnd;
  string karanaName;
  string karanaLord;
  string karanaGod;
  string karanaResult;
  int vara{0};
  string varaName;
  string varaLord;
  float naksh{0};
  string nakshName;
  string nakshLord;
  string nakshGod;
  string nakshResult;
  float yoga{0};
  string yogaName;
};

class muhurta {
 public:
  muhurta();
  muhurta(nativ&);
};
