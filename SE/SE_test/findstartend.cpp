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
  double delta;
  if (nativ.ch.lon < nativ.su.lon) {
    delta = 360.0 + nativ.ch.lon - nativ.su.lon;
  } else {
    delta = nativ.ch.lon - nativ.su.lon;
  }
  cout << "delta-" << delta << endl;

  //  while (delta > 12.0) {
  for (int i = 0; i < 10; ++i) {
    ++aa;

    nativ.chronoBighDateTime -= one_day;  //шаг
    auto datetime = fromCronoToString(nativ.chronoBighDateTime);
    nativ.b_time = fromCronoToTm(nativ.chronoBighDateTime);
    nativ.bday = datetime.first;
    nativ.btime = datetime.second;
    calc();
    printAll(nativ);
    panchang(nativ);
    cout << "aa:" << aa << endl;
  }

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
