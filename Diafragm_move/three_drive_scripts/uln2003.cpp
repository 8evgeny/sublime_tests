#include "uln2003.h"
using namespace std;

void init(int gpio_number) {
    string init ="sh init.sh "+ to_string(gpio_number);
    system(init.c_str());

}
void Pulse::GPIO_HIGH(int number){
// string namefile = "sys/class/gpio/gpio"+ to_string(number)+"/value";
// std::ofstream f(namefile, std::ios::out | std::ios::binary);
// f<<'1';

  string gpio_high="echo 1 > /sys/class/gpio/gpio"+to_string(number)+"/value";
  system(gpio_high.c_str());

}

void Pulse::GPIO_LOW(int number){
//    string namefile = "sys/class/gpio/gpio"+ to_string(number)+"/value";
//    std::ofstream f(namefile, std::ios::out | std::ios::binary);
//    f<<'0';

    string gpio_low="echo 0 > /sys/class/gpio/gpio"+to_string(number)+"/value";
    system(gpio_low.c_str());
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

   open(90);
   PAUSE
   close(90);
   PAUSE
   open(30);

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
    Pulse::a=35;
    Pulse::b=33;
    Pulse::c=36;
    Pulse::d=32;
  }
  if(Move::number_drive!=1){
    Pulse::a=50;
    Pulse::b=54;
    Pulse::c=55;
    Pulse::d=56;
  }
  int count = 0;
  while (1) {
    switch (type_pulse) {
      case 0:
        pulse1(a,b,c,d);
        pulse2(a,b,c,d);
        sleep(a,b,c,d);
        break;
      case 1:
        pulse3(a,b,c,d);
        pulse4(a,b,c,d);
        sleep(a,b,c,d);
        break;
      case 2:
        pulse5(a,b,c,d);
        pulse6(a,b,c,d);
        sleep(a,b,c,d);
        break;
      case 3:
        pulse7(a,b,c,d);
        pulse8(a,b,c,d);
        sleep(a,b,c,d);
        break;
    }
    ++count;
    (type_pulse < 3) ? type_pulse++ : type_pulse = 0;
    if (count == number) break;
  }
  direction_open = true;
  PAUSE
}

void Move::close(int number) {
  if(direction_open){ //при смене направления меняем тип пульса
  if(type_pulse == 0) type_pulse =2;
  if(type_pulse == 1) type_pulse =3;
  if(type_pulse == 2) type_pulse =0;
  if(type_pulse == 3) type_pulse =1;
  }
  if(Move::number_drive==1){
    Pulse::a=35;
    Pulse::b=33;
    Pulse::c=36;
    Pulse::d=32;
  }
  if(Move::number_drive!=1){
    Pulse::a=50;
    Pulse::b=54;
    Pulse::c=55;
    Pulse::d=56;
  }
  int count = 0;
  while (1) {
    switch (type_pulse) {
      case 0:
        pulse8(a,b,c,d);
        pulse7(a,b,c,d);
//        sleep(a,b,c,d);
        break;
      case 1:
        pulse6(a,b,c,d);
        pulse5(a,b,c,d);
//        sleep(a,b,c,d);
        break;
      case 2:
        pulse4(a,b,c,d);
        pulse3(a,b,c,d);
//        sleep(a,b,c,d);
        break;
      case 3:
        pulse2(a,b,c,d);
        pulse1(a,b,c,d);
//        sleep(a,b,c,d);
        break;
    }
    ++count;
    (type_pulse < 3) ? type_pulse++ : type_pulse = 0;
    if (count == number) break;
  }
    direction_open = false;
    PAUSE
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
      open(3);
      std::chrono::milliseconds(2000);
      close(3);
      std::chrono::milliseconds(2000);

//        open(10);
//        for (int i =0; i<3; ++i) {
//          open(1);open(1);open(1);open(1);open(1);open(1);open(1);open(1);open(1);open(1);
//          std::chrono::milliseconds(1000);
//          close(1);close(1);close(1);close(1);close(1);close(1);close(1);close(1);close(1);close(1);
//          std::chrono::milliseconds(1000);
//        }
    }
    if (Move::number_drive==2){
      relay(145,1);
      Move::relay1=ON;
      open(100);
      std::chrono::milliseconds(1000);
      close(100);
      std::chrono::milliseconds(1000);
      relay(145,0);
    }
    if (Move::number_drive==3){
      relay(144,1);
      Move::relay2=ON;
      open(100);
      std::chrono::milliseconds(1000);
      close(100);
      std::chrono::milliseconds(1000);
      relay(144,0);
    }
}

int main() {
    init(32);init(33);init(35);init(36);
    init(50);init(54);init(55);init(56);
    init(144);init(145);


    //    Move focus(2);
    //    Move zoom(3);
    Move diaphragm(1);
    for(int i =0;i<10;++i){
//while(1){
//    diaphragm.drive();
    diaphragm.open(3);
    diaphragm.close(3);
//    std::chrono::seconds(1);
//    focus.drive();
//    zoom.drive();
    }
}



