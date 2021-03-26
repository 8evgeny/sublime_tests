#include "main.h"
#include "nativ.h"

pair<string, string> nativ::dateTimeNowInString() {
  string datenow, timenow;

  chrono::duration<int, ratio<60 * 60 * 24> > one_day(1);
  chrono::duration<int, ratio<60> > one_minut(1);
  chrono::system_clock::time_point today =
      chrono::system_clock::now(); /*-one_minut * 180;  // минус 3 часа
                                    ****!!!*/

  chrono::system_clock::time_point tomorrow = today + one_day;  // !!!

  // chrono(to_time_t)->time_t(*gmtime,*localtime)->tm(strftime)->string
  // string(sscanf)->tm->time_t->chrono

  std::time_t tt, tt_tom;
  tt = chrono::system_clock::to_time_t(today);
  //  std::cout << "today is: " << ctime(&tt);
  tt_tom = chrono::system_clock::to_time_t(tomorrow);
  //  std::cout << "tomorrow will be: " << ctime(&tt_tom);
  // вывод -  today is: Mon Mar 22 22:39:57 2021
  // вывод -  tomorrow will be: Tue Mar 23 22:39:57 2021

  //  time_t now1 = time(0); // это текущее
  time_t now1 = tt;
  struct tm tstruct;
  char date[80];
  char time1[80];
  //  tstruct = *localtime(&now1);

  tstruct = *gmtime(&now1);  // !Заполнили сткуктуру tm в классе

  //  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct); //
  //  2021-03-22.23:03:44
  strftime(date, sizeof(date), "%d-%m-%Y", &tstruct);
  strftime(time1, sizeof(time1), "%X", &tstruct);
  //  cout << "date-" << date << endl;
  //  cout << "time-" << time1 << endl;

  return make_pair(date, time1);
}

chrono::system_clock::time_point nativ::fromStringToCrono(string date,
                                                          string time) {
  chrono::system_clock::time_point result;

  // chrono(to_time_t)->time_t(*gmtime,*localtime)->tm(strftime)->string

  //
  //
  //
  return result;
}

struct tm nativ::fromStringToTm(string dd, string tt) {
  struct tm dt;
  int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0;
  sscanf((dd + tt).c_str(), "%2d-%2d-%4d%2d:%2d:%2d ", &day, &month, &year,
         &hour, &min, &sec);
  dt.tm_year = year - 1900; /* years since 1900 */
  dt.tm_mon = month - 1;
  dt.tm_mday = day;
  dt.tm_hour = hour;
  dt.tm_min = min;
  dt.tm_sec = sec;
  return dt;
}

pair<string, string> nativ::fromTimeToString() {
  //  string date, time;
  char date[11];
  char time[9];
  int year = b_time.tm_year + 1900, month = b_time.tm_mon + 1,
      day = b_time.tm_mday, hour = b_time.tm_hour, min = b_time.tm_min,
      sec = b_time.tm_sec;
  sprintf(time, "%02d:%02d:%02d", hour, min, sec);
  sprintf(date, "%02d-%02d-%04d", day, month, year);
  //  cout << day << month << year << endl;
  //  cout << hour << min << sec << endl;
  //  cout << "date: " << date << endl;
  //  cout << "time: " << time << endl;
  return make_pair<string, string>(date, time);
}

pair<string, string> nativ::findStartTithi() {
  //сохраняем
  tm res = b_time;
  string bday_res = bday;
  string btime_res = btime;

  string datenow, timenow;
  chrono::duration<int, ratio<60 * 60 * 24> > one_day(1);
  chrono::duration<int, ratio<60> > one_minut(1);
  chrono::system_clock::time_point today =
      chrono::system_clock::now(); /*-one_minut * 180;  // минус 3 часа
                                    ****!!!*/

  chrono::system_clock::time_point tomorrow = today + one_day;  // !!!

  //  шагаем  назад;
  double delta = 2.0;
  int aa = 0;
  //  while (delta > 1.0) {
  for (int i = 0; i < 3; ++i) {
    ++aa;
    b_time.tm_mday -= 1;
    if (ch.lon < su.lon) {
      delta = 360.0 + ch.lon - su.lon;
    } else {
      delta = ch.lon - su.lon;
    }
    auto datatime = fromTimeToString();
    bday = datatime.first;
    btime = datatime.second;
    calc();
    printAll();
    panchang();
  }
  //  }
  cout << "aa:" << aa << endl;
  pair<string, string> result;
  result.first = bday;
  result.second = btime;

  //восстанавливаем
  cout << "restored" << endl;
  b_time = res;
  bday = bday_res;
  btime = btime_res;
  calc();
  printAll();
  panchang();

  //  cout << endl
  //       << "start_tithi-" << result.first << " " << result.second << endl;
  return result;
}
