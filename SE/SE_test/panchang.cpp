#include "main.h"
#include "nativ.h"

string nativ::find_vara(string date, string time) {
  time_t result = 0;

  fromStringToTime(date, time);

  result = mktime(&b_time);
  //  cout << ctime(&result) << endl;
  string res = ctime(&result);
  res.erase(3);
  return res;
}

void nativ::printAll() {
  cout << endl
       << this->name << ":  " << this->bday << ", " << this->btime << endl;
  cout << this->city << ", " << this->lon << ", " << this->lat << endl;
  cout << "As-" << this->as.lon << "\t " << this->as.lon << endl;
  cout << "Su-" << this->su.lon << "\t " << this->su.speed << endl;
  cout << "Ch-" << this->ch.lon << "\t " << this->ch.speed << endl;
  cout << "Ma-" << this->ma.lon << "\t " << this->ma.speed << endl;
  cout << "Bu-" << this->bu.lon << "\t " << this->bu.speed << endl;
  cout << "Gu-" << this->gu.lon << "\t " << this->gu.speed << endl;
  cout << "Sk-" << this->sk.lon << "\t " << this->sk.speed << endl;
  cout << "Sa-" << this->sa.lon << "\t " << this->sa.speed << endl;
  cout << "Ra-" << this->ra.lon << "\t " << this->ra.speed << endl;
  cout << "Ke-" << this->ke.lon << "\t " << this->ke.speed << endl;
  cout << endl;
}

void nativ::panchang() {
  varaName = find_vara(bday, btime);
  if (varaName == "Sun") {
    vara = 1;
    varaLord = "Su";
  }
  if (varaName == "Mon") {
    vara = 2;
    varaLord = "Ch";
  }
  if (varaName == "Tue") {
    vara = 3;
    varaLord = "Ma";
  }
  if (varaName == "Wed") {
    vara = 4;
    varaLord = "Bu";
  }
  if (varaName == "Thu") {
    vara = 5;
    varaLord = "Gu";
  }
  if (varaName == "Fri") {
    vara = 6;
    varaLord = "Sk";
  }
  if (varaName == "Sat") {
    vara = 7;
    varaLord = "Sa";
  }
  cout << "Вара\t" << vara << "\t" << varaName << "\t" << varaLord << endl;
  tithi = find_tithi();
  printf("Титхи\t%0.2f\n", tithi);

  naksh = find_naksh();

  switch ((int)naksh + 1) {
    case 1:
      nakshName = "Ашвини";
      break;
    case 2:
      nakshName = "Бхарани";
      break;
    case 3:
      nakshName = "Криттика";
      break;
    case 4:
      nakshName = "Рохини";
      break;
    case 5:
      nakshName = "Мригаширша";
      break;
    case 6:
      nakshName = "Ардра";
      break;
    case 7:
      nakshName = "Пунарвасу";
      break;
    case 8:
      nakshName = "Пушья";
      break;
    case 9:
      nakshName = "Ашлеша";
      break;
    case 10:
      nakshName = "Магха";
      break;
    case 11:
      nakshName = "П.Пхалгуни";
      break;
    case 12:
      nakshName = "У.Пхалгуни";
      break;
    case 13:
      nakshName = "Хаста";
      break;
    case 14:
      nakshName = "Читра";
      break;
    case 15:
      nakshName = "Свати";
      break;
    case 16:
      nakshName = "Вишакха";
      break;
    case 17:
      nakshName = "Анурадха";
      break;
    case 18:
      nakshName = "Джйешттха";
      break;
    case 19:
      nakshName = "Мула";
      break;
    case 20:
      nakshName = "П.Ашадха";
      break;
    case 21:
      nakshName = "У.Ашадха";
      break;
    case 22:
      nakshName = "Шравана";
      break;
    case 23:
      nakshName = "Дхаништха";
      break;
    case 24:
      nakshName = "Шатабхиша";
      break;
    case 25:
      nakshName = "П.Бхадрапада";
      break;
    case 26:
      nakshName = "У.Бхадрапада";
      break;
    case 27:
      nakshName = "Ревати";
      break;
  }
  printf("Накшат\t%0.2f\t%s\n\n", naksh, nakshName.c_str());

  auto ss = findStartTithi();
  cout << endl << "Start_Date: " << ss.first << endl;
  cout << "Start_Time: " << ss.second << endl;

  //  what_karana();
  //  what_yoga();
}

float nativ::find_tithi() {
  double delta;
  if (ch.lon < su.lon) {
    delta = 360.0 + ch.lon - su.lon;
  } else {
    delta = ch.lon - su.lon;
  }
  double tithi = delta / 12;
  return tithi;
}

float nativ::find_naksh() {
  double naksh = ch.lon / 13.33333;
  return naksh;
}

// string nativ::what_karana(){

//    //
//    //
//};

// float nativ::what_yoga() {
//  //
//  //
//}
