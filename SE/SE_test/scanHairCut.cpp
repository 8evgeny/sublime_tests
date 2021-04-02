#include "main.h"
#include "nativ.h"

void nativ::scanHairCut(nativ& nativ, int numDay) {
  int num = numDay * 24;

  auto tpoint = this->chronoBighDateTime;
  while (num > 0) {
    int navatara = 0;
    //    if ((this->naksh - nativ.naksh) >= 0) {
    //      navatara = 1 + (int)this->naksh - (int)nativ.naksh;
    //    } else {
    //      navatara = 27 + (int)this->naksh - (int)nativ.naksh;
    //    }

    chrono::duration<int, ratio<60> > one_minut(1);

    cout << "\r" << num << " час"
         << " navatara: " << navatara << " ";
    tpoint += one_minut * 60;
    auto datetime = fromCronoToString(tpoint);
    cout << datetime.second << endl;
    this->b_time = fromCronoToTm(tpoint);
    this->bday = datetime.first;
    this->btime = datetime.second;
    calc();
    panchang(*this);
    --num;
  }
}
