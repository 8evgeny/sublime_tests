#include "diaphragm.h"
using namespace std;
int position;
int type_pulse =0;
bool direction_open;
void open(int number) {
    if(!direction_open){ //при смене направления меняем тип пульса
      if(type_pulse == 0) type_pulse =2;
      if(type_pulse == 1) type_pulse =3;
      if(type_pulse == 2) type_pulse =1;
      if(type_pulse == 3) type_pulse =0;
    }
  int count = 0;
  while (1) {
    switch (type_pulse) {
      case 0:
        pulse1();
        pulse2();
        break;
      case 1:
        pulse3();
        pulse4();
        break;
      case 2:
        pulse5();
        pulse6();
        break;
      case 3:
        pulse7();
        pulse8();
        break;
    }
    ++count;
    (type_pulse < 3) ? type_pulse++ : type_pulse = 0;
    if (count == number) break;
  }
      direction_open = true;
}
void close(int number) {
    if(direction_open){ //при смене направления меняем тип пульса
      if(type_pulse == 0) type_pulse =2;
      if(type_pulse == 1) type_pulse =3;
      if(type_pulse == 2) type_pulse =1;
      if(type_pulse == 3) type_pulse =0;
    }
  int count = 0;
  while (1) {
    switch (type_pulse) {
      case 2:
        pulse8();
        pulse7();
        break;
      case 3:
        pulse6();
        pulse5();
        break;
      case 0:
        pulse4();
        pulse3();
        break;
      case 1:
        pulse2();
        pulse1();
        break;
    }
    ++count;
    (type_pulse < 3) ? type_pulse++ : type_pulse = 0;
    if (count == number) break;
  }
        direction_open = false;
}
void init() {
  wiringPiSetup();
  pinMode(GPIO32, OUTPUT);
  pinMode(GPIO33, OUTPUT);
  pinMode(GPIO35, OUTPUT);
  pinMode(GPIO36, OUTPUT);

  position = 0;
}

int main() {
  init();

open(90);
close(90);
open(30);

  while (1) {
//    test();

//for (int i=1;i<90;++i){ open(1);  delay(50); }
//delay(500);
//for (int i=1;i<90;++i){ close(1); delay(50); }
//delay(500);

open(1);delay(100);open(1);delay(100);open(1);delay(100);open(1);delay(100);open(1);delay(100);open(1);delay(100);
delay(500);
close(1);delay(100);close(1);delay(100);close(1);delay(100);close(1);delay(100);close(1);delay(100);close(1);delay(100);
delay(500);


//open(88);
//delay(500);
//close(88);
//delay(500);
  }

}
