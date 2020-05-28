#include "move.h"
using namespace std;
int position;

void init() {
  wiringPiSetup();
  string init="sh init.sh";
  system(init.c_str());

}

Pulse::Pulse(int aa,int bb,int cc,int dd){
    a=aa;
    b=bb;
    c=cc;
    d=dd;
}
Pulse::Pulse(){
}

Move::Move(int number_drive){
   Move::number_drive=number_drive;
   Move::relay1=OFF;
   Move::relay2=OFF;
   relay(145,OFF);
   relay(144,OFF);
//   open(90);
//   delay(200);
//   close(90);
//   delay(200);
//   open(30);
 }
Move::~Move(){
    relay(145,OFF);
    relay(144,OFF);
}


void Move::open(int number) {
      if(!direction_open){ //при смене направления меняем тип пульса
        if(type_pulse == 0) type_pulse =2;
        if(type_pulse == 1) type_pulse =3;
        if(type_pulse == 2) type_pulse =0;
        if(type_pulse == 3) type_pulse =1;
      }
     if(Move::number_drive==1){
     Pulse::a=GPIO35;
     Pulse::b=GPIO33;
     Pulse::c=GPIO36;
     Pulse::d=GPIO32;
    }
    if(Move::number_drive!=1){
     Pulse::a=GPIO50;
     Pulse::b=GPIO54;
     Pulse::c=GPIO55;
     Pulse::d=GPIO56;
    }
  int count = 0;
  while (1) {
    switch (type_pulse) {
      case 0:
        pulse1(a,b,c,d);
        pulse2(a,b,c,d);
        break;
      case 1:
        pulse3(a,b,c,d);
        pulse4(a,b,c,d);
        break;
      case 2:
        pulse5(a,b,c,d);
        pulse6(a,b,c,d);
        break;
      case 3:
        pulse7(a,b,c,d);
        pulse8(a,b,c,d);
        break;
    }
    ++count;
    (type_pulse < 3) ? type_pulse++ : type_pulse = 0;
    if (count == number) break;
  }
    direction_open = true;
}
void Move::close(int number) {
      if(direction_open){ //при смене направления меняем тип пульса
      if(type_pulse == 0) type_pulse =2;
      if(type_pulse == 1) type_pulse =3;
      if(type_pulse == 2) type_pulse =0;
      if(type_pulse == 3) type_pulse =1;
      }
    if(Move::number_drive==1){
     Pulse::a=GPIO35;
     Pulse::b=GPIO33;
     Pulse::c=GPIO36;
     Pulse::d=GPIO32;
    }
    if(Move::number_drive!=1){
     Pulse::a=GPIO50;
     Pulse::b=GPIO54;
     Pulse::c=GPIO55;
     Pulse::d=GPIO56;
    }
  int count = 0;
  while (1) {
    switch (type_pulse) {
    case 0:
      pulse8(a,b,c,d);
      pulse7(a,b,c,d);
      break;
    case 1:
      pulse6(a,b,c,d);
      pulse5(a,b,c,d);
      break;
    case 2:
      pulse4(a,b,c,d);
      pulse3(a,b,c,d);
      break;
    case 3:
      pulse2(a,b,c,d);
      pulse1(a,b,c,d);
      break;
  }
  ++count;
  (type_pulse < 3) ? type_pulse++ : type_pulse = 0;
  if (count == number) break;
  }
  direction_open = false;
}
void Move::relay(int number, int state){
    if (state == ON){ //управляется низким потенциалом
        string gpio_low="sh GPIO_LOW.sh " + to_string(number);
        system(gpio_low.c_str());

        if(number==1) {Move::relay1=ON;Move::relay2=OFF;Move::relay3=OFF;}
        if(number==2) {Move::relay2=ON;Move::relay1=OFF;Move::relay3=OFF;}
        if(number==3) {Move::relay3=ON;Move::relay1=OFF;Move::relay2=OFF;}
    }
    if (state == OFF){

        string gpio_hi="sh GPIO_HIGH.sh " + to_string(number);
        system(gpio_hi.c_str());
        if(number==1) Move::relay1=OFF;
        if(number==2) Move::relay2=OFF;
        if(number==3) Move::relay3=OFF;
    }
 }

void Move::drive(){
    if (Move::number_drive==1){
        relay(145,OFF);
        relay(144,OFF);

      open(1);
      delay(500);
      close(1);
      delay(500);
    }
    if (Move::number_drive==2){
      relay(145,1);
      Move::relay1=ON;
      open(200);
      delay(500);
      close(200);
      delay(500);
      relay(145,0);

    }
    if (Move::number_drive==3){
      relay(144,1);
      Move::relay2=ON;
      open(300);
      delay(500);
      close(300);
      delay(500);
      relay(144,0);

    }
}

int main() {
    init();
    Move diaphragm(1);
    diaphragm.open(90);
    diaphragm.close(90);
    diaphragm.open(25);

//    Move focus(2);
//    Move x(3);
    while (1) {
     for(int i=1;i<30;++i){
     diaphragm.open(1); delay(10);
     }
    delay(500);
    for(int i=1;i<30;++i){
    diaphragm.close(1); delay(10);
    }
    delay(500);

//    focus.drive();
//    delay(500);
//    x.drive();
//    delay(500);
   }
}
