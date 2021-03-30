#include "main.h"
#include "nativ.h"

void nativ::printAll(nativ& nativ) {
  cout << endl;
  cout << "\r" << nativ.name << ":  " << nativ.bday << ", " << nativ.btime
       << endl;
  cout << nativ.city << ", " << nativ.lon << ", " << nativ.lat << endl;
  cout << "As-" << nativ.as.lon << "\t " << endl;
  cout << "Su-" << nativ.su.lon << "\t " << nativ.su.speed << endl;
  cout << "Ch-" << nativ.ch.lon << "\t " << nativ.ch.speed << endl;
  cout << "Ma-" << nativ.ma.lon << "\t " << nativ.ma.speed << endl;
  cout << "Bu-" << nativ.bu.lon << "\t " << nativ.bu.speed << endl;
  cout << "Gu-" << nativ.gu.lon << "\t " << nativ.gu.speed << endl;
  cout << "Sk-" << nativ.sk.lon << "\t " << nativ.sk.speed << endl;
  cout << "Sa-" << nativ.sa.lon << "\t " << nativ.sa.speed << endl;
  cout << "Ra-" << nativ.ra.lon << "\t " << nativ.ra.speed << endl;
  cout << "Ke-" << nativ.ke.lon << "\t " << nativ.ke.speed << endl;
}

tuple<string, int, string> nativ::findVarafromTm(struct tm& b_time) {
  //  cout << "findVarafromTm_b_time.tm_wday: " << b_time.tm_wday << endl;
  tuple<string, int, string> tuple;
  switch (b_time.tm_wday) {
    case 1: {
      tuple = {"Понедельник", 2, "Ch"};
      break;
    }
    case 2: {
      tuple = {"Вторник", 3, "Ma"};
      break;
    }
    case 3: {
      tuple = {"Среда", 4, "Bu"};
      break;
    }
    case 4: {
      tuple = {"Четверг", 5, "Gu"};
      break;
    }
    case 5: {
      tuple = {"Пятница", 6, "Sk"};
      break;
    }
    case 6: {
      tuple = {"Суббота", 7, "Sa"};

      break;
    }
    case 0: {
      tuple = {"Воскресенье", 1, "Su"};
      break;
    }
  }
  return tuple;
}

void nativ::panchangPrint(nativ& nativ) {
  system("export COLUMNS=140");
  system("export LINES=40");

  //  int moonDay = 1; //Иногда улетает назад
  int moonDaystart = (int)tithi + 1;
  auto startTithi = findStartTithi(*this, moonDaystart);
  //  int moonDayend = 17;
  int moonDayend = (int)tithi + 1;
  auto endTithi = findEndTithi(*this, moonDayend);

  cout << "\n"
       << setprecision(4) << "Вара " << setw(8) << nativ.vara << setw(38) << ""
       << nativ.varaName << setw(7) << nativ.varaLord << endl;

  //  printf("Титхи\t%0.2f\t%s\t%s\t%s\t%s\n", nativ.tithi,
  //  nativ.tithiName.c_str(),
  //         nativ.tithiLord.c_str(), nativ.tithiGod.c_str(),
  //         nativ.tithiResult.c_str());

  cout << setprecision(4) << "Титхи " << setw(10) << nativ.tithi << setw(10)
       << startTithi.first.erase(5) << " " << startTithi.second.erase(5)
       << " - " << endTithi.first.erase(5) << " " << endTithi.second.erase(5)
       << "     " << nativ.tithiName << setw(12) << nativ.tithiLord << setw(16)
       << nativ.tithiGod << setw(55) << nativ.tithiResult << endl;

  //  printf("Накш\t%0.2f\t%s\t%s\t%s\n", nativ.naksh, nativ.nakshName.c_str(),
  //         nativ.nakshLord.c_str(), nativ.nakshGod.c_str());

  cout << setprecision(4) << "Накшатра "  //<< setfill('*')
       << setw(8) << nativ.naksh << setw(44) << nativ.nakshName << setw(13)
       << nativ.nakshLord << setw(4) << "" << nativ.nakshGod << endl;
}

void nativ::panchang(nativ& nativ) {
  auto tupleVara = findVarafromTm(nativ.b_time);
  nativ.varaName = get<0>(tupleVara);
  nativ.vara = get<1>(tupleVara);
  nativ.varaLord = get<2>(tupleVara);

  auto tupleTithi = findTithi(nativ);
  nativ.tithi = get<0>(tupleTithi);
  nativ.tithiName = get<1>(tupleTithi);
  nativ.tithiLord = get<2>(tupleTithi);
  nativ.tithiGod = get<3>(tupleTithi);
  nativ.tithiResult = get<4>(tupleTithi);

  auto tupleNaksh = findNaksh(nativ);
  nativ.naksh = get<0>(tupleNaksh);
  nativ.nakshName = get<1>(tupleNaksh);
  nativ.nakshLord = get<2>(tupleNaksh);
  nativ.nakshGod = get<3>(tupleNaksh);

  //  what_karana();
  //  what_yoga();
}

tuple<double, string, string, string, string> nativ::findTithi(nativ& nativ) {
  double delta;
  if (nativ.ch.lon < nativ.su.lon) {
    delta = 360.0 + nativ.ch.lon - nativ.su.lon;
  } else {
    delta = nativ.ch.lon - nativ.su.lon;
  }
  double tithi = delta / 12;
  tuple<double, string, string, string, string> tuple;

  switch ((int)tithi + 1) {
    case 1:
      tuple = {tithi, "Пратипат", "Su", "Агни", "Процветание"};
      break;
    case 16:
      tuple = {tithi, "Пратипат", "Su", "Агни", "Процветание"};
      break;
    case 2:
      tuple = {tithi, "Двития", "Ch", "Брахма", "Благоприятные"};
      break;
    case 17:
      tuple = {tithi, "Двития", "Ch", "Брахма", "Благоприятные"};
      break;
    case 3:
      tuple = {tithi, "Трития", "Ma", "Гаури (Парвати)", "Сила"};
      break;
    case 18:
      tuple = {tithi, "Трития", "Ma", "Гаури (Парвати)", "Сила"};
      break;
    case 4:
      tuple = {tithi, "Чатурти", "Bu", "Ганеша", "Зло, Проклятие"};
      break;
    case 19:
      tuple = {tithi, "Чатурти", "Bu", "Ганеша", "Зло, Проклятие"};
      break;
    case 5:
      tuple = {tithi, "Панчами", "Gu", "Нага", "Богатство, Процветание"};
      break;
    case 20:
      tuple = {tithi, "Панчами", "Gu", "Нага", "Богатство, Процветание"};
      break;
    case 6:
      tuple = {tithi, "Шашти", "Sk", "Картикея", "Слава"};
      break;
    case 21:
      tuple = {tithi, "Шашти", "Sk", "Картикея", "Слава"};
      break;
    case 7:
      tuple = {tithi, "Саптами", "Sa", "Сурья", "Друг, покровитель"};
      break;
    case 22:
      tuple = {tithi, "Саптами", "Sa", "Сурья", "Друг, покровитель"};
      break;
    case 8:
      tuple = {tithi, "Аштами", "Ra", "Шива(Махеша)", "Враждебность, Конфликт"};
      break;
    case 23:
      tuple = {tithi, "Аштами", "Ra", "Шива(Махеша)", "Враждебность, Конфликт"};
      break;
    case 9:
      tuple = {tithi, "Навами", "Su", "Дурга", "Аргессивные"};
      break;
    case 24:
      tuple = {tithi, "Навами", "Su", "Дурга", "Аргессивные"};
      break;
    case 10:
      tuple = {tithi, "Дашами", "Ch", "Яма", "Мягкие"};
      break;
    case 25:
      tuple = {tithi, "Дашами", "Ch", "Яма", "Мягкие"};
      break;
    case 11:
      tuple = {tithi, "Экадаши", "Ma", "Вишвадевы", "Радость, Счастье"};
      break;
    case 26:
      tuple = {tithi, "Экадаши", "Ma", "Вишвадевы", "Радость, Счастье"};
      break;
    case 12:
      tuple = {tithi, "Двадаши", "Bu", "Вишну", "Слава"};
      break;
    case 27:
      tuple = {tithi, "Двадаши", "Bu", "Вишну", "Слава"};
      break;
    case 13:
      tuple = {tithi, "Трайодаши", "Gu", "Камадев", "Победные"};
      break;
    case 28:
      tuple = {tithi, "Трайодаши", "Gu", "Камадев", "Победные"};
      break;
    case 14:
      tuple = {tithi, "Чатурдаши", "Sk", "Шива", "Агрессивные"};
      break;
    case 29:
      tuple = {tithi, "Чатурдаши", "Sk", "Шива", "Агрессивные"};
      break;
    case 15:
      tuple = {tithi, "Пурнима", "Sa", "Сома (Чандра)", "Мягкие"};
      break;
    case 30:
      tuple = {tithi, "Амавасья", "Ra", "Питри (Саптариши)",
               "Неблагоприятные, Злые"};
      break;
  }
  return tuple;
}

tuple<double, string, string, string> nativ::findNaksh(nativ& nativ) {
  tuple<double, string, string, string> tuple;
  double naksh = nativ.ch.lon / 13.33333;
  switch ((int)naksh + 1) {
    case 1:
      tuple = {naksh, "Ашвини", "Ke", "Ашвини Кумары"};
      break;
    case 2:
      tuple = {naksh, "Бхарани", "Sk", "Яма"};
      break;
    case 3:
      tuple = {naksh, "Криттика", "Su", "Агни"};
      break;
    case 4:
      tuple = {naksh, "Рохини", "Ch", "Брахма"};
      break;
    case 5:
      tuple = {naksh, "Мригашира", "Ma", "Сома, бог Луны"};
      break;
    case 6:
      tuple = {naksh, "Ардра", "Ra", "Рудра-воплощение Шивы"};
      break;
    case 7:
      tuple = {naksh, "Пунарвасу", "Gu", "Адити, богиня Вечности"};
      break;
    case 8:
      tuple = {naksh, "Пушья", "Sa", "Брихаспати"};
      break;
    case 9:
      tuple = {naksh, "Ашлеша", "Bu", "Наги"};
      break;
    case 10:
      tuple = {naksh, "Магха", "Ke", "Питри-предки"};
      break;
    case 11:
      tuple = {naksh, "П.Пхалгуни", "Sk", "Бхага-ведический бог Удачи"};
      break;
    case 12:
      tuple = {naksh, "У.Пхалгуни", "Su", "Арьяман"};
      break;
    case 13:
      tuple = {naksh, "Хаста", "Ch", "Савитур, бог Солнца"};
      break;
    case 14:
      tuple = {naksh, "Читра", "Ma", "Тваштар-небесный архитектор"};
      break;
    case 15:
      tuple = {naksh, "Свати", "Ra", "Вайю,бог ветра и дыхание жизни"};
      break;
    case 16:
      tuple = {naksh, "Вишакха    ", "Gu", "Агни-бог огня и Индра-бог богов"};
      break;
    case 17:
      tuple = {naksh, "Анурадха   ", "Sa", "Митра, бог света"};
      break;
    case 18:
      tuple = {naksh, "Джйештха  ", "Bu", "Индра, бог богов"};
      break;
    case 19:
      tuple = {naksh, "Мула", "Ke", "Ниритти"};
      break;
    case 20:
      tuple = {naksh, "П.Ашадха", "Sk", " Апас, бог воды"};
      break;
    case 21:
      tuple = {naksh, "У.Ашадха", "Su", "Вишвадэваты-боги вселенной"};
      break;
    case 22:
      tuple = {naksh, "Шравана", "Ch", "Вишну-хранитель вселенной"};
      break;
    case 23:
      tuple = {naksh, "Дхаништха", "Ma", "Восемь васу"};
      break;
    case 24:
      tuple = {naksh, "Шатабхиша", "Ra", "Варуна, бог морей"};
      break;
    case 25:
      tuple = {naksh, "П.Бхадрапада", "Gu", "Айя Экапада-одноногий козел"};
      break;
    case 26:
      tuple = {naksh, "У.Бхадрапада", "Sa", " Ахир Будхния"};
      break;
    case 27:
      tuple = {naksh, "Ревати", "Bu", "Пушан"};
      break;
  }
  return tuple;
}

// string nativ::what_karana(){

//    //
//    //
//};

// float nativ::what_yoga() {
//  //
//  //
//}
