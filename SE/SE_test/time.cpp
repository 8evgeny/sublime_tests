#include "main.h"
#include "nativ.h"

pair<string, string> nativ::dateTimeNowInString() {
  string datenow, timenow;

  chrono::duration<int, ratio<60 * 60 * 24> > one_day(1);
  chrono::duration<int, ratio<60> > one_minut(1);
  chrono::duration<int, ratio<1> > one_second(1);
  chrono::system_clock::time_point today =
      chrono::system_clock::now() + one_day * 0;

  chrono::system_clock::time_point tomorrow = today + one_day * 1;  // !!!

  // chrono(to_time_t)->time_t(*gmtime,*localtime)->tm(strftime)->string
  // string(sscanf)->tm(mktime)->time_t(from_time_t)->chrono

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
                                                          string ttime) {
  // chrono(to_time_t)->time_t(*gmtime,*localtime)->tm(strftime)->string
  // string(sscanf)->tm(mktime)->time_t(from_time_t)->chrono

  struct tm step1 = fromStringToTm(date, ttime);
  struct tm* pt = &step1;

  time_t step2;
  time(&step2);

  const char* weekday[] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                           "Thursday", "Friday", "Saturday"};

  pt = gmtime(&step2);
  mktime(pt);

  //  printf("That day is a %s.\n", weekday[pt->tm_wday]);

  chrono::system_clock::time_point result =
      chrono::system_clock::from_time_t(step2);
  return result;
}

pair<string, string> nativ::fromCronoToString(
    chrono::system_clock::time_point tpoint) {
  // chrono(to_time_t)->time_t(*gmtime,*localtime)->tm(strftime)->string
  // string(sscanf)->tm(mktime)->time_t(from_time_t)->chrono

  tm step2 = fromCronoToTm(tpoint);

  char date[80];
  char time[80];
  strftime(date, sizeof(date), "%d-%m-%Y", &step2);
  strftime(time, sizeof(time), "%X", &step2);

  return make_pair(date, time);
}

struct tm nativ::fromCronoToTm(chrono::system_clock::time_point tpoint) {
  time_t step1 = chrono::system_clock::to_time_t(tpoint);
  tm result = *gmtime(&step1);

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

  time_t result = mktime(&dt);
  //  cout << ctime(&result) << endl;
  string res = ctime(&result);
  varaName = res.erase(3);

  return dt;
}

pair<string, string> nativ::fromTmToString(tm& b_time) {
  //  string date, time;
  char date[11];
  char time[9];
  int year = b_time.tm_year + 1900, month = b_time.tm_mon + 1,
      day = b_time.tm_mday, hour = b_time.tm_hour, min = b_time.tm_min,
      sec = b_time.tm_sec;
  sprintf(time, "%02d:%02d:%02d", hour, min, sec);
  sprintf(date, "%02d-%02d-%04d", day, month, year);

  return make_pair<string, string>(date, time);
}