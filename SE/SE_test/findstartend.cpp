#include "main.h"
#include "nativ.h"

pair<string, string> nativ::findStartTithi(nativ& nativ) {
  //сохраняем
  auto res = nativ.chronoBighDateTime;

  // chrono(to_time_t)->time_t(*gmtime,*localtime)->tm(strftime)->string
  // string(sscanf)->tm(mktime)->time_t(from_time_t)->chrono

  //  string datenow, timenow;
  chrono::duration<int, ratio<60 * 60 * 24> > one_day(1);
  chrono::duration<int, ratio<60> > one_minut(1);
  chrono::system_clock::time_point tpoint = nativ.chronoBighDateTime;

  //  шагаем  назад;
  int aa = 0;
  double delta = 13;
  //  while (delta > 12.0) {
  if (nativ.ch.lon < nativ.su.lon) {
    delta = 360.0 + nativ.ch.lon - nativ.su.lon;
  } else {
    delta = nativ.ch.lon - nativ.su.lon;
  }
  cout << "delta-" << delta << endl;

  ++aa;
  cout << "step back " << aa << endl;

  tpoint -= (one_minut * 60 * 24 * ((int)nativ.tithi + 1) +
             one_minut * 45 * (int)nativ.tithi);  //шаг
  auto datetime = fromCronoToString(tpoint);
  nativ.b_time = fromCronoToTm(tpoint);
  nativ.bday = datetime.first;
  nativ.btime = datetime.second;
  calc();
  printAll(nativ);
  panchang(nativ);
  delta = nativ.ch.lon - nativ.su.lon;
  cout << "deltaNew-" << delta << endl;
  //  }

  pair<string, string> result;
  result.first = nativ.bday;
  result.second = nativ.btime;

  //восстанавливаем
  cout << "restored" << endl;
  nativ.chronoBighDateTime = res;

  auto datetimeold = fromCronoToString(nativ.chronoBighDateTime);
  nativ.b_time = fromCronoToTm(nativ.chronoBighDateTime);
  nativ.bday = datetimeold.first;
  nativ.btime = datetimeold.second;
  calc();
  printAll(nativ);
  panchang(*this);

  //  cout << endl
  //       << "start_tithi-" << result.first << " " << result.second << endl;
  return result;
}
