#include "main.h"
#include "nativ.h"

void nativ::scanHairCut(nativ& nativ, int numDay) {
  int num = numDay * 24 * 4;
  auto res = this->chronoBighDateTime;
  auto tpoint = this->chronoBighDateTime;
  int navatara = 0;
  cout << "Расчитываются результаты на " << numDay << " дней вперед." << endl;
  cout << "\rСтрижка для: " << nativ.name << " благоприятна:" << endl;

  vector<pair<chrono::system_clock::time_point, string>> goodTime;

  while (num > 0) {
    auto TinTuple = findTithi(*this);
    //    cout << "tithi: " << 1 + (int)get<0>(TinTuple) << endl;

    chrono::duration<int, ratio<60>> one_minut(1);
    tpoint += one_minut * 15;
    auto datetime = fromCronoToString(tpoint);
    auto toPrint = fromCronoToStringlocal(tpoint);
    this->b_time = fromCronoToTm(tpoint);
    this->bday = datetime.first;
    this->btime = datetime.second;
    calc();
    panchang(*this);
    if (((int)this->naksh - (int)nativ.naksh) >= 0) {
      navatara = 1 + (int)this->naksh - (int)nativ.naksh;
    } else {
      navatara = 28 + (int)this->naksh - (int)nativ.naksh;
    }
    //    Можно в накшатре Пушйа, Пунарвасу, Ревати, Хаста, Шравана, Дханишта,
    //    Мригашира, Ашвини, Читра, Джйешта, Сатабиша и Свати.
    //         1,5,7,8,13,14,15,18,22,23,24,27
    //   1,2,3,5,6,7,10,11,12,13,15

    //    Стрижка всегда должна выполняться утром
    //Понедельник, среда, четверг и пятница удачны

    //        cout << "\r+" << 1 + numDay * 24 - num << " час" << " navatara: "
    //        << navatara << " " << datetime.second << endl;

    int t = 1 + (int)this->tithi;
    int n = 1 + (int)this->naksh;
    if ((n == 1) || (n == 5) || (n == 7) || (n == 8) || (n == 13) ||
        (n == 14) || (n == 15) || (n == 18) || (n == 22) || (n == 23) ||
        (n == 24) || (n == 27)) {
      if ((this->b_time.tm_hour < 11) && (this->b_time.tm_hour > 6)) {
        if ((t == 1) || (t == 2) || (t == 3) || (t == 5) || (t == 6) ||
            (t == 7) || (t == 10) || (t == 11) || (t == 12) || (t == 13) ||
            (t == 15)) {
          if ((navatara == 2) || (navatara == 11) || (navatara == 20)) {
            goodTime.push_back(make_pair(tpoint, "Богатство"));
          }
          if ((navatara == 4) || (navatara == 13) || (navatara == 22)) {
            goodTime.push_back(make_pair(tpoint, "Процветание"));
          }
          if ((navatara == 6) || (navatara == 15) || (navatara == 24)) {
            goodTime.push_back(make_pair(tpoint, "Достижение"));
          }
          if ((navatara == 8) || (navatara == 17) || (navatara == 26)) {
            goodTime.push_back(make_pair(tpoint, "Друг"));
          }
          if ((navatara == 9) || (navatara == 18) || (navatara == 27)) {
            goodTime.push_back(make_pair(tpoint, "Хороший друг"));
          }
        }  //условие титхи
      }    //условие утром
    }      //условие накшатра

    --num;
  }
  for (auto i : goodTime) {
    cout << fromCronoToStringlocal(i.first).first << " "
         << fromCronoToStringlocal(i.first).second << " " << i.second << endl;
  }
  //восстанавливаем
  this->chronoBighDateTime = res;
  auto datetimeold = fromCronoToString(this->chronoBighDateTime);
  this->b_time = fromCronoToTm(nativ.chronoBighDateTime);
  this->bday = datetimeold.first;
  this->btime = datetimeold.second;
  calc();
  panchang(*this);
  this->tithiStart = tpoint;
}
