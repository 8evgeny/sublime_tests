#include "main.h"
#include "nativ.h"

pair<string, string> nativ::findStartTithi(nativ& nativ, int number) {
  //сохраняем
  auto res = nativ.chronoBighDateTime;

  // chrono(to_time_t)->time_t(*gmtime,*localtime)->tm(strftime)->string
  // string(sscanf)->tm(mktime)->time_t(from_time_t)->chrono

  //  string datenow, timenow;
  chrono::duration<int, ratio<60 * 60 * 24> > one_day(1);
  chrono::duration<int, ratio<60> > one_minut(1);
  chrono::system_clock::time_point tpoint = nativ.chronoBighDateTime;

  //  шагаем  назад;
  double delta = 0;
  if (nativ.ch.lon < nativ.su.lon) {
    delta = 360.0 + nativ.ch.lon - nativ.su.lon;
  } else {
    delta = nativ.ch.lon - nativ.su.lon;
  }
  //  cout << "delta: " << delta << endl;
  //  cout << "big step back " << endl;

  tpoint -=
      (one_minut * 60 * 24 * ((int)nativ.tithi - number) + one_minut * 1150);
  auto datetime = fromCronoToString(tpoint);
  nativ.b_time = fromCronoToTm(tpoint);
  nativ.bday = datetime.first;
  nativ.btime = datetime.second;
  calc();
  //  printAll(nativ);
  panchang(nativ);

  delta = nativ.ch.lon - nativ.su.lon;
  if (delta < 0) delta += 360;
  //  cout << "deltaNew: " << delta << endl;
  int i = 0;

  while (nativ.tithi > 0.005) {
    ++i;
    cout << "\r5 min back " << i << endl;
    tpoint -= one_minut * 5;

    auto datetime = fromCronoToString(tpoint);
    nativ.b_time = fromCronoToTm(tpoint);
    nativ.bday = datetime.first;
    nativ.btime = datetime.second;
    calc();
    panchang(nativ);
  }
  cout << "\r\nfind first tithi" << endl;
  printAll(nativ);
  panchangPrint(nativ);

  pair<string, string> result;
  result.first = nativ.bday;

  result.second = nativ.btime;

  //восстанавливаем
  cout << "\nrestored" << endl;
  nativ.chronoBighDateTime = res;

  auto datetimeold = fromCronoToString(nativ.chronoBighDateTime);
  nativ.b_time = fromCronoToTm(nativ.chronoBighDateTime);
  nativ.bday = datetimeold.first;
  nativ.btime = datetimeold.second;
  calc();
  printAll(nativ);
  panchang(*this);
  panchangPrint(*this);
  //  cout << endl
  //       << "start_tithi-" << result.first << " " << result.second << endl;
  return result;
}
