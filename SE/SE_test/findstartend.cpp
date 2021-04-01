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
  //  cout << "big step back " << endl;
  auto numDayBack = (number - 1 - (int)nativ.tithi) >= 0
                        ? (number - 1 - (int)nativ.tithi)
                        : (1 + (int)nativ.tithi - number);
  auto part =
      (nativ.tithi - (int)nativ.tithi) * 60 * 24 * 0.84;  //коэфф подобран
  tpoint -=
      one_minut * (int)part + one_minut * int(numDayBack * 60 * 24 * 0.85);
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

  while (nativ.tithi > number - 1 + 0.001) {
    ++i;
    if (i == 1) {  //после большого шага
                   //      printAll(nativ);
                   //      panchangPrint(*this);
    }

    //    cout << "\r5 min back " << i << endl;
    tpoint -= one_minut * 1;

    auto datetime = fromCronoToString(tpoint);
    nativ.b_time = fromCronoToTm(tpoint);
    nativ.bday = datetime.first;
    nativ.btime = datetime.second;
    calc();
    panchang(nativ);
  }
  //  cout << "\r\nfind first tithi" << endl;
  //  printAll(nativ);
  //  panchangPrint(nativ);
  auto result = fromCronoToStringlocal(tpoint);

  //восстанавливаем
  //  cout << "\nrestored" << endl;
  nativ.chronoBighDateTime = res;

  auto datetimeold = fromCronoToString(nativ.chronoBighDateTime);
  nativ.b_time = fromCronoToTm(nativ.chronoBighDateTime);
  nativ.bday = datetimeold.first;
  nativ.btime = datetimeold.second;
  calc();
  //  printAll(nativ);
  panchang(*this);
  //  panchangPrint(*this);
  nativ.tithiStart = tpoint;
  return result;
}

pair<string, string> nativ::findEndTithi(nativ& nativ, int number) {
  //сохраняем
  auto res = nativ.chronoBighDateTime;

  // chrono(to_time_t)->time_t(*gmtime,*localtime)->tm(strftime)->string
  // string(sscanf)->tm(mktime)->time_t(from_time_t)->chrono

  //  string datenow, timenow;
  chrono::duration<int, ratio<60 * 60 * 24> > one_day(1);
  chrono::duration<int, ratio<60> > one_minut(1);
  chrono::system_clock::time_point tpoint = nativ.chronoBighDateTime;

  //  шагаем  вперед;
  double delta = 0;
  if (nativ.ch.lon < nativ.su.lon) {
    delta = 360.0 + nativ.ch.lon - nativ.su.lon;
  } else {
    delta = nativ.ch.lon - nativ.su.lon;
  }
  //  cout << "big step forward " << endl;

  auto numDayForward = (number - 1 - (int)nativ.tithi) >= 0
                           ? (number - 1 - (int)nativ.tithi)
                           : (1 + (int)nativ.tithi - number);

  auto part =
      (1 - nativ.tithi + (int)nativ.tithi) * 60 * 24 * 0.84;  //коэфф подобран
  tpoint +=
      one_minut * (int)part + one_minut * int(numDayForward * 60 * 24 * 0.85);
  //  tpoint += one_minut * (int)part;

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

  while (nativ.tithi < (int)nativ.tithi + 1 - 0.001) {
    ++i;
    if (i == 1) {  //после большого шага
                   //      printAll(nativ);
                   //      panchangPrint(*this);
    }

    //    cout << "\r5 min forward " << i << endl;
    tpoint += one_minut * 1;

    auto datetime = fromCronoToString(tpoint);
    nativ.b_time = fromCronoToTm(tpoint);
    nativ.bday = datetime.first;
    nativ.btime = datetime.second;
    calc();
    panchang(nativ);
  }
  //  cout << "\r\nfind first tithi" << endl;
  //  printAll(nativ);
  //  panchangPrint(nativ);
  auto result = fromCronoToStringlocal(tpoint);

  //восстанавливаем
  //  cout << "\nrestored" << endl;
  nativ.chronoBighDateTime = res;

  auto datetimeold = fromCronoToString(nativ.chronoBighDateTime);
  nativ.b_time = fromCronoToTm(nativ.chronoBighDateTime);
  nativ.bday = datetimeold.first;
  nativ.btime = datetimeold.second;
  calc();
  //  printAll(nativ);
  panchang(*this);
  //  panchangPrint(*this);
  nativ.tithiEnd = tpoint;
  return result;
}

pair<string, string> nativ::findStartNaksh(nativ& nativ, int number) {
  //сохраняем
  auto res = nativ.chronoBighDateTime;

  // chrono(to_time_t)->time_t(*gmtime,*localtime)->tm(strftime)->string
  // string(sscanf)->tm(mktime)->time_t(from_time_t)->chrono

  chrono::duration<int, ratio<60 * 60 * 24> > one_day(1);
  chrono::duration<int, ratio<60> > one_minut(1);
  chrono::system_clock::time_point tpoint = nativ.chronoBighDateTime;

  //  шагаем  назад;

  //  cout << "big step back " << endl;
  //  auto numDayBack = (number - 1 - (int)nativ.tithi) >= 0
  //                        ? (number - 1 - (int)nativ.tithi)
  //                        : (1 + (int)nativ.tithi - number);
  auto part = (nativ.naksh - (int)nativ.naksh) * 26.6666 *
              0.996;  // 26.666  часов в 1 накшатре
  tpoint -=
      one_minut * (int)part;  // + one_minut * int(numDayBack * 60 * 24 * 0.85);
  auto datetime = fromCronoToString(tpoint);
  nativ.b_time = fromCronoToTm(tpoint);
  nativ.bday = datetime.first;
  nativ.btime = datetime.second;
  calc();
  //  printAll(nativ);
  panchang(nativ);

  int i = 0;

  while (nativ.naksh > number - 1 + 0.003) {
    ++i;
    if (i == 1) {  //после большого шага
                   //      printAll(nativ);
                   //      panchangPrint(*this);
    }

    //    cout << "\r1 min back " << i << endl;
    tpoint -= one_minut * 3;

    auto datetime = fromCronoToString(tpoint);
    nativ.b_time = fromCronoToTm(tpoint);
    nativ.bday = datetime.first;
    nativ.btime = datetime.second;
    calc();
    panchang(nativ);
  }

  //  printAll(nativ);
  //  panchangPrint(nativ);
  auto result = fromCronoToStringlocal(tpoint);

  //восстанавливаем
  //  cout << "\nrestored" << endl;
  nativ.chronoBighDateTime = res;

  auto datetimeold = fromCronoToString(nativ.chronoBighDateTime);
  nativ.b_time = fromCronoToTm(nativ.chronoBighDateTime);
  nativ.bday = datetimeold.first;
  nativ.btime = datetimeold.second;
  calc();
  printAll(nativ);
  panchang(*this);
  panchangPrint(*this);

  return result;
}

pair<string, string> nativ::findEndNaksh(nativ& nativ, int number) {
  //сохраняем
  auto res = nativ.chronoBighDateTime;

  // chrono(to_time_t)->time_t(*gmtime,*localtime)->tm(strftime)->string
  // string(sscanf)->tm(mktime)->time_t(from_time_t)->chrono

  //  string datenow, timenow;
  chrono::duration<int, ratio<60 * 60 * 24> > one_day(1);
  chrono::duration<int, ratio<60> > one_minut(1);
  chrono::system_clock::time_point tpoint = nativ.chronoBighDateTime;

  //  шагаем  вперед;

  //  auto numDayForward = (number - 1 - (int)nativ.tithi) >= 0
  //                           ? (number - 1 - (int)nativ.tithi)
  //                           : (1 + (int)nativ.tithi - number);

  auto part = (1 - nativ.naksh + (int)nativ.naksh) * 26.6666 *
              0.996;  // 26.666  часов в 1 накшатре
  tpoint += one_minut *
            (int)part;  // + one_minut * int(numDayForward * 60 * 24 * 0.85);

  auto datetime = fromCronoToString(tpoint);
  nativ.b_time = fromCronoToTm(tpoint);
  nativ.bday = datetime.first;
  nativ.btime = datetime.second;
  calc();
  //  printAll(nativ);
  panchang(nativ);

  int i = 0;

  while (nativ.naksh < (int)nativ.naksh + 1 - 0.003) {
    ++i;
    if (i == 1) {  //после большого шага
                   //      printAll(nativ);
                   //      panchangPrint(*this);
    }

    tpoint += one_minut * 3;

    auto datetime = fromCronoToString(tpoint);
    nativ.b_time = fromCronoToTm(tpoint);
    nativ.bday = datetime.first;
    nativ.btime = datetime.second;
    calc();
    panchang(nativ);
  }

  //  printAll(nativ);
  //  panchangPrint(nativ);
  auto result = fromCronoToStringlocal(tpoint);

  //восстанавливаем
  //  cout << "\nrestored" << endl;
  nativ.chronoBighDateTime = res;

  auto datetimeold = fromCronoToString(nativ.chronoBighDateTime);
  nativ.b_time = fromCronoToTm(nativ.chronoBighDateTime);
  nativ.bday = datetimeold.first;
  nativ.btime = datetimeold.second;
  calc();
  //  printAll(nativ);
  panchang(*this);
  //  panchangPrint(*this);

  return result;
}

pair<string, string> nativ::findStartKarana(nativ& nativ) {
  bool numKaranaInTithi = false;
  if ((nativ.tithi - (int)nativ.tithi) > 0.5) numKaranaInTithi = true;
  if (!numKaranaInTithi) {
    nativ.karanaStart = nativ.tithiStart;
  }
  if (numKaranaInTithi) {
    nativ.karanaEnd = nativ.tithiEnd;
    auto durationTithi = nativ.tithiEnd - nativ.tithiStart;
    auto halfdurationTithi = durationTithi / 2;
    nativ.karanaStart = nativ.tithiStart + halfdurationTithi;
  }
  return fromCronoToStringlocal(nativ.karanaStart);
}

pair<string, string> nativ::findEndKarana(nativ& nativ) {
  bool numKaranaInTithi = false;
  if ((nativ.tithi - (int)nativ.tithi) > 0.5) numKaranaInTithi = true;
  if (numKaranaInTithi) {
    nativ.karanaEnd = nativ.tithiEnd;
  }
  if (!numKaranaInTithi) {
    nativ.karanaStart = nativ.tithiStart;
    auto durationTithi = nativ.tithiEnd - nativ.tithiStart;
    auto halfdurationTithi = durationTithi / 2;
    nativ.karanaEnd = nativ.tithiStart + halfdurationTithi;
  }
  return fromCronoToStringlocal(nativ.karanaEnd);
}
