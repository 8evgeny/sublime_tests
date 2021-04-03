#include "main.h"
#include "nativ.h"

void nativ::planetInSignsInHouses() {
  as.sign = as.lon / 30 + 1;
  as.house = 1;
  su.sign = su.lon / 30 + 1;
  su.sign - as.sign >= 0 ? su.house = su.sign - as.sign + 1
                         : su.house = 13 + su.sign - as.sign;
  ch.sign = ch.lon / 30 + 1;
  ch.sign - as.sign >= 0 ? ch.house = ch.sign - as.sign + 1
                         : ch.house = 13 + ch.sign - as.sign;
  ma.sign = ma.lon / 30 + 1;
  ma.sign - as.sign >= 0 ? ma.house = ma.sign - as.sign + 1
                         : ma.house = 13 + ma.sign - as.sign;
  bu.sign = bu.lon / 30 + 1;
  bu.sign - as.sign >= 0 ? bu.house = bu.sign - as.sign + 1
                         : bu.house = 13 + bu.sign - as.sign;
  gu.sign = gu.lon / 30 + 1;
  gu.sign - as.sign >= 0 ? gu.house = gu.sign - as.sign + 1
                         : gu.house = 13 + gu.sign - as.sign;
  sk.sign = sk.lon / 30 + 1;
  sk.sign - as.sign >= 0 ? sk.house = sk.sign - as.sign + 1
                         : sk.house = 13 + sk.sign - as.sign;
  sa.sign = sa.lon / 30 + 1;
  sa.sign - as.sign >= 0 ? sa.house = sa.sign - as.sign + 1
                         : sa.house = 13 + sa.sign - as.sign;
  ra.sign = ra.lon / 30 + 1;
  ra.sign - as.sign >= 0 ? ra.house = ra.sign - as.sign + 1
                         : ra.house = 13 + ra.sign - as.sign;
  ke.sign = ke.lon / 30 + 1;
  ke.sign - as.sign >= 0 ? ke.house = ke.sign - as.sign + 1
                         : ke.house = 13 + ke.sign - as.sign;
}

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
  //  //  int moonDay = 1; //Иногда улетает назад
  //  int moonDaystart = (int)tithi + 1;
  //  auto startTithi = findStartTithi(*this, moonDaystart);
  //  //  int moonDayend = 17;
  //  int moonDayend = (int)tithi + 1;
  //  auto endTithi = findEndTithi(*this, moonDayend);

  //  cout << "\n"
  //       << setprecision(4) << "Вара " << setw(8) << nativ.vara << setw(38) <<
  //       ""
  //       << nativ.varaName << setw(7) << nativ.varaLord << endl;

  //  printf("Титхи\t%0.2f\t%s\t%s\t%s\t%s\n", nativ.tithi,
  //  nativ.tithiName.c_str(),
  //         nativ.tithiLord.c_str(), nativ.tithiGod.c_str(),
  //         nativ.tithiResult.c_str());

  //  cout << setprecision(4) << "Титхи " << setw(10) << nativ.tithi << setw(10)
  //       << startTithi.first.erase(5) << " " << startTithi.second.erase(5)
  //       << " - " << endTithi.first.erase(5) << " " <<
  //       endTithi.second.erase(5)
  //       << "     " << nativ.tithiName << setw(12) << nativ.tithiLord <<
  //       setw(16)
  //       << nativ.tithiGod << setw(55) << nativ.tithiResult << endl;

  //  printf("Накш\t%0.2f\t%s\t%s\t%s\n", nativ.naksh, nativ.nakshName.c_str(),
  //         nativ.nakshLord.c_str(), nativ.nakshGod.c_str());

  //  cout << setprecision(4) << "Накшатра "  //<< setfill('*')
  //       << setw(8) << nativ.naksh << setw(44) << nativ.nakshName << setw(13)
  //       << nativ.nakshLord << setw(4) << "" << nativ.nakshGod << endl;
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
  nativ.nakshResult = get<4>(tupleNaksh);

  auto tupleKarana = findKarana(nativ);
  nativ.karana = get<0>(tupleKarana);
  nativ.karanaName = get<1>(tupleKarana);
  nativ.karanaLord = get<2>(tupleKarana);
  nativ.karanaGod = get<3>(tupleKarana);
  nativ.karanaResult = get<4>(tupleKarana);

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

tuple<double, string, string, string, string> nativ::findNaksh(nativ& nativ) {
  tuple<double, string, string, string, string> tuple;
  double naksh = nativ.ch.lon / 13.33333;
  switch ((int)naksh + 1) {
    case 1:
      tuple = {naksh, "Ашвини", "Ke", "Ашвини Кумары", " "};
      break;
    case 2:
      tuple = {naksh, "Бхарани", "Sk", "Яма", " "};
      break;
    case 3:
      tuple = {naksh, "Криттика", "Su", "Агни", " "};
      break;
    case 4:
      tuple = {naksh, "Рохини", "Ch", "Брахма", " "};
      break;
    case 5:
      tuple = {naksh, "Мригашира", "Ma", "Сома, бог Луны", " "};
      break;
    case 6:
      tuple = {naksh, "Ардра", "Ra", "Рудра-воплощение Шивы", " "};
      break;
    case 7:
      tuple = {naksh, "Пунарвасу", "Gu", "Адити, богиня Вечности", " "};
      break;
    case 8:
      tuple = {naksh, "Пушья", "Sa", "Брихаспати", " "};
      break;
    case 9:
      tuple = {naksh, "Ашлеша", "Bu", "Наги", " "};
      break;
    case 10:
      tuple = {naksh, "Магха", "Ke", "Питри-предки", " "};
      break;
    case 11:
      tuple = {naksh, "П.Пхалгуни", "Sk", "Бхага-ведический бог Удачи", " "};
      break;
    case 12:
      tuple = {naksh, "У.Пхалгуни", "Su", "Арьяман", " "};
      break;
    case 13:
      tuple = {naksh, "Хаста", "Ch", "Савитур, бог Солнца", " "};
      break;
    case 14:
      tuple = {naksh, "Читра", "Ma", "Тваштар-небесный архитектор", " "};
      break;
    case 15:
      tuple = {naksh, "Свати", "Ra", "Вайю,бог ветра и дыхание жизни",
               "Индивидуальность  - ключевое слово Свати. "
               "Недолговечные, скоротечные дела и вещи, покупка"
               "транспортных средств, садоводство, путешествия."
               " Максимально благоприятна для секса. Можно стричься. Удачно "
               "начало образования. "};
      break;
    case 16:
      tuple = {
          naksh, "Вишакха", "Gu", "Агни-бог огня и Индра-бог богов",
          "Не начинать новую важную работу. Благоприятны повседневные дела, "
          "рутинная работа. Единственная накшатра с двумя "
          "божествами. Агни - священный огонь, "
          "представляет огонь ума, огонь стремления и пламя интеллекта. "
          "Агни - это также Кундалини, наш скрытый огонь. Индра наслаждается "
          "чувственными удовольствиями и роскошью,"
          "но он также уничтожает демонов, а разрушение внутренних демонов "
          "позволяет духовным энергиям течь  беспрепятственно"};
      break;
    case 17:
      tuple = {naksh, "Анурадха", "Sa", "Митра, бог света",
               "Максимально благоприятна для секса"};
      break;
    case 18:
      tuple = {naksh, "Джйештха", "Bu", "Индра, бог богов", " "};
      break;
    case 19:
      tuple = {naksh, "Мула", "Ke", "Ниритти", " "};
      break;
    case 20:
      tuple = {naksh, "П.Ашадха", "Sk", "Апас, бог воды", " "};
      break;
    case 21:
      tuple = {naksh, "У.Ашадха", "Su", "Вишвадэваты-боги вселенной", " "};
      break;
    case 22:
      tuple = {naksh, "Шравана", "Ch", "Вишну-хранитель вселенной", " "};
      break;
    case 23:
      tuple = {naksh, "Дхаништха", "Ma", "Восемь васу", " "};
      break;
    case 24:
      tuple = {naksh, "Шатабхиша", "Ra", "Варуна, бог морей", " "};
      break;
    case 25:
      tuple = {naksh, "П.Бхадрапада", "Gu", "Айя Экапада-одноногий козел", " "};
      break;
    case 26:
      tuple = {naksh, "У.Бхадрапада", "Sa", "Ахир Будхния", " "};
      break;
    case 27:
      tuple = {naksh, "Ревати", "Bu", "Пушан", " "};
      break;
  }
  return tuple;
}

tuple<int, string, string, string, string> nativ::findKarana(nativ& nativ) {
  bool numKaranaInTithi = false;
  if ((nativ.tithi - (int)nativ.tithi) > 0.5) numKaranaInTithi = true;
  switch ((int)nativ.tithi) {
    case 0: {
      if (!numKaranaInTithi) {
        nativ.karana = 10;
        nativ.karanaName = "Нага";
        nativ.karanaLord = "Ra";
        nativ.karanaGod = "Нага";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 11;
        nativ.karanaName = "Кинстугхвнв";
        nativ.karanaLord = "Ke";
        nativ.karanaGod = "Вайю";
        nativ.karanaResult = "";
      }
      break;
    }
    case 1: {
      if (!numKaranaInTithi) {
        nativ.karana = 1;
        nativ.karanaName = "Бава";
        nativ.karanaLord = "Su";
        nativ.karanaGod = "Индра";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 2;
        nativ.karanaName = "Балава";
        nativ.karanaLord = "Ch";
        nativ.karanaGod = "Брахма";
        nativ.karanaResult = "";
      }
      break;
    }
    case 2: {
      if (!numKaranaInTithi) {
        nativ.karana = 3;
        nativ.karanaName = "Каулава";
        nativ.karanaLord = "Ma";
        nativ.karanaGod = "Митра";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 4;
        nativ.karanaName = "Тайтилая";
        nativ.karanaLord = "Bu";
        nativ.karanaGod = "Арьяман";
        nativ.karanaResult = "";
      }
      break;
    }
    case 3: {
      if (!numKaranaInTithi) {
        nativ.karana = 5;
        nativ.karanaName = "Гара";
        nativ.karanaLord = "Gu";
        nativ.karanaGod = "Индра";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 6;
        nativ.karanaName = "Ваниджа";
        nativ.karanaLord = "Sk";
        nativ.karanaGod = "Лакшми";
        nativ.karanaResult = "";
      }
      break;
    }
    case 4: {
      if (!numKaranaInTithi) {
        nativ.karana = 7;
        nativ.karanaName = "Вишти";
        nativ.karanaLord = "Sa";
        nativ.karanaGod = "Яма";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 1;
        nativ.karanaName = "Бава";
        nativ.karanaLord = "Su";
        nativ.karanaGod = "Индра";
        nativ.karanaResult = "";
      }
      break;
    }
    case 5: {
      if (!numKaranaInTithi) {
        nativ.karana = 2;
        nativ.karanaName = "Балава";
        nativ.karanaLord = "Ch";
        nativ.karanaGod = "Брахма";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 3;
        nativ.karanaName = "Каулава";
        nativ.karanaLord = "Ma";
        nativ.karanaGod = "Митра";
        nativ.karanaResult = "";
      }
      break;
    }
    case 6: {
      if (!numKaranaInTithi) {
        nativ.karana = 4;
        nativ.karanaName = "Тайтилая";
        nativ.karanaLord = "Bu";
        nativ.karanaGod = "Арьяман";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 5;
        nativ.karanaName = "Гара";
        nativ.karanaLord = "Gu";
        nativ.karanaGod = "Индра";
        nativ.karanaResult = "";
      }
      break;
    }
    case 7: {
      if (!numKaranaInTithi) {
        nativ.karana = 6;
        nativ.karanaName = "Ваниджа";
        nativ.karanaLord = "Sk";
        nativ.karanaGod = "Лакшми";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 7;
        nativ.karanaName = "Вишти";
        nativ.karanaLord = "Sa";
        nativ.karanaGod = "Яма";
        nativ.karanaResult = "";
      }
      break;
    }
    case 8: {
      if (!numKaranaInTithi) {
        nativ.karana = 1;
        nativ.karanaName = "Бава";
        nativ.karanaLord = "Su";
        nativ.karanaGod = "Индра";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 2;
        nativ.karanaName = "Балава";
        nativ.karanaLord = "Ch";
        nativ.karanaGod = "Брахма";
        nativ.karanaResult = "";
      }
      break;
    }
    case 9: {
      if (!numKaranaInTithi) {
        nativ.karana = 3;
        nativ.karanaName = "Каулава";
        nativ.karanaLord = "Ma";
        nativ.karanaGod = "Митра";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 4;
        nativ.karanaName = "Тайтилая";
        nativ.karanaLord = "Bu";
        nativ.karanaGod = "Арьяман";
        nativ.karanaResult = "";
      }
      break;
    }
    case 10: {
      if (!numKaranaInTithi) {
        nativ.karana = 5;
        nativ.karanaName = "Гара";
        nativ.karanaLord = "Gu";
        nativ.karanaGod = "Индра";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 6;
        nativ.karanaName = "Ваниджа";
        nativ.karanaLord = "Sk";
        nativ.karanaGod = "Лакшми";
        nativ.karanaResult = "";
      }
      break;
    }
    case 11: {
      if (!numKaranaInTithi) {
        nativ.karana = 7;
        nativ.karanaName = "Вишти";
        nativ.karanaLord = "Sa";
        nativ.karanaGod = "Яма";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 1;
        nativ.karanaName = "Бава";
        nativ.karanaLord = "Su";
        nativ.karanaGod = "Индра";
        nativ.karanaResult = "";
      }
      break;
    }
    case 12: {
      if (!numKaranaInTithi) {
        nativ.karana = 2;
        nativ.karanaName = "Балава";
        nativ.karanaLord = "Ch";
        nativ.karanaGod = "Брахма";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 3;
        nativ.karanaName = "Каулава";
        nativ.karanaLord = "Ma";
        nativ.karanaGod = "Митра";
        nativ.karanaResult = "";
      }
      break;
    }
    case 13: {
      if (!numKaranaInTithi) {
        nativ.karana = 4;
        nativ.karanaName = "Тайтилая";
        nativ.karanaLord = "Bu";
        nativ.karanaGod = "Арьяман";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 5;
        nativ.karanaName = "Гара";
        nativ.karanaLord = "Gu";
        nativ.karanaGod = "Индра";
        nativ.karanaResult = "";
      }
      break;
    }
    case 14: {
      if (!numKaranaInTithi) {
        nativ.karana = 6;
        nativ.karanaName = "Ваниджа";
        nativ.karanaLord = "Sk";
        nativ.karanaGod = "Лакшми";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 7;
        nativ.karanaName = "Вишти";
        nativ.karanaLord = "Sa";
        nativ.karanaGod = "Яма";
        nativ.karanaResult = "";
      }
      break;
    }
    case 15: {
      if (!numKaranaInTithi) {
        nativ.karana = 1;
        nativ.karanaName = "Бава";
        nativ.karanaLord = "Su";
        nativ.karanaGod = "Индра";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 2;
        nativ.karanaName = "Балава";
        nativ.karanaLord = "Ch";
        nativ.karanaGod = "Брахма";
        nativ.karanaResult = "";
      }
      break;
    }
    case 16: {
      if (!numKaranaInTithi) {
        nativ.karana = 3;
        nativ.karanaName = "Каулава";
        nativ.karanaLord = "Ma";
        nativ.karanaGod = "Митра";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 4;
        nativ.karanaName = "Тайтилая";
        nativ.karanaLord = "Bu";
        nativ.karanaGod = "Арьяман";
        nativ.karanaResult = "";
      }
      break;
    }
    case 17: {
      if (!numKaranaInTithi) {
        nativ.karana = 5;
        nativ.karanaName = "Гара";
        nativ.karanaLord = "Gu";
        nativ.karanaGod = "Индра";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 6;
        nativ.karanaName = "Ваниджа";
        nativ.karanaLord = "Sk";
        nativ.karanaGod = "Лакшми";
        nativ.karanaResult = "";
      }
      break;
    }
    case 18: {
      if (!numKaranaInTithi) {
        nativ.karana = 7;
        nativ.karanaName = "Вишти";
        nativ.karanaLord = "Sa";
        nativ.karanaGod = "Яма";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 1;
        nativ.karanaName = "Бава";
        nativ.karanaLord = "Su";
        nativ.karanaGod = "Индра";
        nativ.karanaResult = "";
      }
      break;
    }
    case 19: {
      if (!numKaranaInTithi) {
        nativ.karana = 2;
        nativ.karanaName = "Балава";
        nativ.karanaLord = "Ch";
        nativ.karanaGod = "Брахма";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 3;
        nativ.karanaName = "Каулава";
        nativ.karanaLord = "Ma";
        nativ.karanaGod = "Митра";
        nativ.karanaResult = "";
      }
      break;
    }
    case 20: {
      if (!numKaranaInTithi) {
        nativ.karana = 4;
        nativ.karanaName = "Тайтилая";
        nativ.karanaLord = "Bu";
        nativ.karanaGod = "Арьяман";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 5;
        nativ.karanaName = "Гара";
        nativ.karanaLord = "Gu";
        nativ.karanaGod = "Индра";
        nativ.karanaResult = "";
      }
      break;
    }
    case 21: {
      if (!numKaranaInTithi) {
        nativ.karana = 6;
        nativ.karanaName = "Ваниджа";
        nativ.karanaLord = "Sk";
        nativ.karanaGod = "Лакшми";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 7;
        nativ.karanaName = "Вишти";
        nativ.karanaLord = "Sa";
        nativ.karanaGod = "Яма";
        nativ.karanaResult = "";
      }
      break;
    }
    case 22: {
      if (!numKaranaInTithi) {
        nativ.karana = 1;
        nativ.karanaName = "Бава";
        nativ.karanaLord = "Su";
        nativ.karanaGod = "Индра";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 2;
        nativ.karanaName = "Балава";
        nativ.karanaLord = "Ch";
        nativ.karanaGod = "Брахма";
        nativ.karanaResult = "";
      }
      break;
    }
    case 23: {
      if (!numKaranaInTithi) {
        nativ.karana = 3;
        nativ.karanaName = "Каулава";
        nativ.karanaLord = "Ma";
        nativ.karanaGod = "Митра";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 4;
        nativ.karanaName = "Тайтилая";
        nativ.karanaLord = "Bu";
        nativ.karanaGod = "Арьяман";
        nativ.karanaResult = "";
      }
      break;
    }
    case 24: {
      if (!numKaranaInTithi) {
        nativ.karana = 5;
        nativ.karanaName = "Гара";
        nativ.karanaLord = "Gu";
        nativ.karanaGod = "Индра";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 6;
        nativ.karanaName = "Ваниджа";
        nativ.karanaLord = "Sk";
        nativ.karanaGod = "Лакшми";
        nativ.karanaResult = "";
      }
      break;
    }
    case 25: {
      if (!numKaranaInTithi) {
        nativ.karana = 7;
        nativ.karanaName = "Вишти";
        nativ.karanaLord = "Sa";
        nativ.karanaGod = "Яма";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 1;
        nativ.karanaName = "Бава";
        nativ.karanaLord = "Su";
        nativ.karanaGod = "Индра";
        nativ.karanaResult = "";
      }
      break;
    }
    case 26: {
      if (!numKaranaInTithi) {
        nativ.karana = 2;
        nativ.karanaName = "Балава";
        nativ.karanaLord = "Ch";
        nativ.karanaGod = "Брахма";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 3;
        nativ.karanaName = "Каулава";
        nativ.karanaLord = "Ma";
        nativ.karanaGod = "Митра";
        nativ.karanaResult = "";
      }

      break;
    }
    case 27: {
      if (!numKaranaInTithi) {
        nativ.karana = 4;
        nativ.karanaName = "Тайтилая";
        nativ.karanaLord = "Bu";
        nativ.karanaGod = "Арьяман";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 5;
        nativ.karanaName = "Гара";
        nativ.karanaLord = "Gu";
        nativ.karanaGod = "Индра";
        nativ.karanaResult = "";
      }
      break;
    }
    case 28: {
      if (!numKaranaInTithi) {
        nativ.karana = 6;
        nativ.karanaName = "Ваниджа";
        nativ.karanaLord = "Sk";
        nativ.karanaGod = "Лакшми";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 7;
        nativ.karanaName = "Вишти";
        nativ.karanaLord = "Sa";
        nativ.karanaGod = "Яма";
        nativ.karanaResult = "";
      }
      break;
    }
    case 29: {
      if (!numKaranaInTithi) {
        nativ.karana = 8;
        nativ.karanaName = "Шакуни";
        nativ.karanaLord = "Ra";
        nativ.karanaGod = "Нага";
        nativ.karanaResult = "";
      } else {
        nativ.karana = 9;
        nativ.karanaName = "Чатушпада";
        nativ.karanaLord = "Ke";
        nativ.karanaGod = "Брахма";
        nativ.karanaResult = "";
      }
      break;
    }
  }
  tuple<int, string, string, string, string> result = {
      nativ.karana, nativ.karanaName, nativ.karanaLord, nativ.karanaGod,
      nativ.karanaResult};
  return result;
}

string nativ::navatara(nativ& nativ) {
  int navatara = 0;
  if (((int)this->naksh - (int)nativ.naksh) >= 0) {
    navatara = 1 + (int)this->naksh - (int)nativ.naksh;
  } else {
    navatara = 28 + (int)this->naksh - (int)nativ.naksh;
  }

  if ((navatara == 1) || (navatara == 10) || (navatara == 19))
    return "Опасность";
  if ((navatara == 2) || (navatara == 11) || (navatara == 20))
    return "Богатство";
  if ((navatara == 3) || (navatara == 12) || (navatara == 21))
    return "Опасность";
  if ((navatara == 4) || (navatara == 13) || (navatara == 22))
    return "Процветание";
  if ((navatara == 5) || (navatara == 14) || (navatara == 23))
    return "Препятствия";
  if ((navatara == 6) || (navatara == 15) || (navatara == 24))
    return "Достижение";
  if ((navatara == 7) || (navatara == 16) || (navatara == 25)) return "Смерть";
  if ((navatara == 8) || (navatara == 17) || (navatara == 26)) return "Друг";
  if ((navatara == 9) || (navatara == 18) || (navatara == 27))
    return "Хороший друг";
}

// float nativ::what_yoga() {
//  //
//  //
//}
