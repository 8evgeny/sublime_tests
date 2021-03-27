#include "main.h"
#include "nativ.h"

void nativ::printAll(nativ& nativ) {
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
      tuple = {"Воскресенье", 3, "Su"};
      break;
    }
  }
  return tuple;
}

void nativ::panchang(nativ& nativ) {
  auto tupleVara = findVarafromTm(nativ.b_time);
  nativ.varaName = get<0>(tupleVara);
  nativ.vara = get<1>(tupleVara);
  nativ.varaLord = get<2>(tupleVara);

  cout << "Вара. Огонь. Энергия\t" << nativ.vara << "\t" << nativ.varaName
       << "  \t" << nativ.varaLord << endl;

  auto tupleTithi = findTithi(nativ);
  nativ.tithi = get<0>(tupleTithi);
  nativ.tithiName = get<1>(tupleTithi);
  nativ.tithiLord = get<2>(tupleTithi);
  nativ.tithiGod = get<3>(tupleTithi);
  nativ.tithiResult = get<4>(tupleTithi);

  printf("Титхи. Вода – исполнение желаний\t%0.2f%s\t%s\t%s\t%s\n", nativ.tithi,
         nativ.tithiName.c_str(), nativ.tithiLord.c_str(),
         nativ.tithiGod.c_str(), nativ.tithiResult.c_str());

  auto tupleNaksh = find_naksh(nativ);
  nativ.naksh = get<0>(tupleNaksh);
  nativ.nakshName = get<1>(tupleNaksh);
  nativ.nakshLord = get<2>(tupleNaksh);
  nativ.nakshGod = get<3>(tupleNaksh);
  printf("Накшатра. Воздух – вожжи колесницы\t%0.2f\t%s\t%s\t%s\n", nativ.naksh,
         nativ.nakshName.c_str(), nativ.nakshLord.c_str(),
         nativ.nakshGod.c_str());
  cout << endl;

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
      tuple = {tithi, "Двития", "Ch", "Брахма", "Благоприятные"};
      break;
    case 18:
      tuple = {tithi, "Двития", "Ch", "Брахма", "Благоприятные"};
      break;
  }
  return tuple;
}

tuple<double, string, string, string> nativ::find_naksh(nativ& nativ) {
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
      tuple = {naksh, "Рохини   ", "Ch", "Брахма"};
      break;
    case 5:
      tuple = {naksh, "Мригашира", "Ma", "Сома, Бог Луны"};
      break;
    case 6:
      tuple = {naksh, "Ардра     ", "Ra", "Рудра-воплощение Шивы"};
      break;
    case 7:
      tuple = {naksh, "Пунарвасу", "Gu", "Адити, богиня Вечности"};
      break;
    case 8:
      tuple = {naksh, "Пушья     ", "Sa", " Брихаспати"};
      break;
    case 9:
      tuple = {naksh, "Ашлеша    ", "Bu", "Наги"};
      break;
    case 10:
      tuple = {naksh, "Магха     ", "Ke", " Питри-предки"};
      break;
    case 11:
      tuple = {naksh, "П.Пхалгуни", "Sk", "Бхага-Ведический Бог Удачи"};
      break;
    case 12:
      tuple = {naksh, "У.Пхалгуни", "Su", "Арьяман"};
      break;
    case 13:
      tuple = {naksh, "Хаста      ", "Ch", "Савитур, Бог Солнца"};
      break;
    case 14:
      tuple = {naksh, "Читра       ", "Ma", " Тваштар-Небесный Архитектор"};
      break;
    case 15:
      tuple = {naksh, "Свати        ", "Ra",
               " Вайю, Бог Ветра и Дыхание Жизни"};
      break;
    case 16:
      tuple = {naksh, "Вишакха    ", "Gu", "Агни-Бог Огня и Индра-Бог Богов"};
      break;
    case 17:
      tuple = {naksh, "Анурадха   ", "Sa", "Митра, Бог Света"};
      break;
    case 18:
      tuple = {naksh, "Джйештха  ", "Bu", "Индра, Бог Богов"};
      break;
    case 19:
      tuple = {naksh, "Мула", "Ke", "Ниритти"};
      break;
    case 20:
      tuple = {naksh, "П.Ашадха", "Sk", " Апас, Бог Воды"};
      break;
    case 21:
      tuple = {naksh, "У.Ашадха", "Su", "Вишвадэваты-Боги Вселенной"};
      break;
    case 22:
      tuple = {naksh, "Шравана", "Ch", "Вишну-Хранитель Вселенной"};
      break;
    case 23:
      tuple = {naksh, "Дхаништха", "Ma", "Восемь Васу"};
      break;
    case 24:
      tuple = {naksh, "Шатабхиша", "Ra", "Варуна, Бог морей"};
      break;
    case 25:
      tuple = {naksh, "П.Бхадрапада", "Gu", "Айя Экапада-Одноногий козел"};
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
