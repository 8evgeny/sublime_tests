#pragma once
#include <wiringPi.h>
#include <iostream>


#define GPIO32 7  //pin7  черный
#define GPIO33 0  //pin11 желтый
#define GPIO35 2  //pin13 белый
#define GPIO36 3  //pin15 красный

#define GPIO50 1  //pin12
#define GPIO54 4  //pin16
#define GPIO55 5  //pin18
#define GPIO56 6  //pin22

#define GPIO145 15  //pin8
#define GPIO144 16  //pin10
#define GPIO149 11  //pin26

#define DELAY delayMicroseconds(5000)
#define INTERSECT delayMicroseconds(2000)

#define ON 1
#define OFF 0

  class Pulse {
      public:

      bool direction_open;
      int a;
      int b;
      int c;
      int d;
      Pulse(int,int,int,int);
      Pulse();
//      ~Pulse();
    void pulse1(int,int,int,int);
    void pulse2(int,int,int,int);
    void pulse3(int,int,int,int);
    void pulse4(int,int,int,int);
    void pulse5(int,int,int,int);
    void pulse6(int,int,int,int);
    void pulse7(int,int,int,int);
    void pulse8(int,int,int,int);
    void sleep(int,int,int,int);
  };
  class Move:Pulse{
     public:
     int type_pulse=0;
     int number_drive;
     int relay1;
     int relay2;
     int relay3;
       Move(int);
       ~Move();
//       ~Move();
     void open(int);
     void close(int);
     void relay(int , int);
     void drive();
     void init();
 };

  void test();
  void test2();

