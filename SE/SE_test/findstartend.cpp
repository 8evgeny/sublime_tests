#include "main.h"
#include "nativ.h"

pair<string, string> nativ::findStartTithi() {
  //сохраняем
  auto res = chronoBighDateTime;
  // chrono(to_time_t)->time_t(*gmtime,*localtime)->tm(strftime)->string
  // string(sscanf)->tm(mktime)->time_t(from_time_t)->chrono

  //  string datenow, timenow;
  chrono::duration<int, ratio<60 * 60 * 24> > one_day(1);
  chrono::duration<int, ratio<60> > one_minut(1);
  chrono::system_clock::time_point tpoint = chronoBighDateTime;

  //  шагаем  назад;
  int aa = 0;
  double delta;
  if (ch.lon < su.lon) {
    delta = 360.0 + ch.lon - su.lon;
  } else {
    delta = ch.lon - su.lon;
  }
  cout << "delta-" << delta << endl;

  //  while (delta > 12.0) {
  ++aa;

  chronoBighDateTime -= one_day;  //шаг
  auto datetime = fromCronoToString(chronoBighDateTime);
  b_time = fromCronoToTm(chronoBighDateTime);
  bday = datetime.first;
  btime = datetime.second;
  calc();

  printAll();

  panchang();
  //  }

  cout << "aa:" << aa << endl;

  pair<string, string> result;
  result.first = bday;
  result.second = btime;

  //восстанавливаем
  cout << "restored" << endl;
  chronoBighDateTime = res;
  auto datetimeold = fromCronoToString(chronoBighDateTime);
  b_time = fromCronoToTm(chronoBighDateTime);
  bday = datetimeold.first;
  btime = datetimeold.second;
  calc();
  printAll();
  panchang();

  //  cout << endl
  //       << "start_tithi-" << result.first << " " << result.second << endl;
  return result;
}
