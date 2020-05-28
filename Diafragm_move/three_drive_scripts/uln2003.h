#pragma once
//#include <wiringPi.h>
#include <chrono>
#include <ctime>
#include <thread>
#include <iostream>
#include <fstream>
//Работает на TOKINE
#define one 32
#define two 33
#define three 35
#define four 36
#define ON 1
#define OFF 0
#define DELAY delay(5);
#define INTERSECT delay(5);
#define SLEEP delay(5);
#define PAUSE delay(1000);
class Pulse {
    public:
    int a;
    int b;
    int c;
    int d;
    int type_pulse=0;
    bool direction_open;
    Pulse(int,int,int,int);
    Pulse();
  void pulse1(int,int,int,int);
  void pulse2(int,int,int,int);
  void pulse3(int,int,int,int);
  void pulse4(int,int,int,int);
  void pulse5(int,int,int,int);
  void pulse6(int,int,int,int);
  void pulse7(int,int,int,int);
  void pulse8(int,int,int,int);
  void sleep(int,int,int,int);
  void delay(int);
  void GPIO_HIGH(int );
  void GPIO_LOW(int );
  void delay (std::string);
};
class Move:Pulse{
   public:
   int number_drive;
   int relay1;
   int relay2;
   int relay3;
     Move(int);
     ~Move();
   void open(int);
   void close(int);
   void relay(int , int);
   void drive();
   void init();
};

void test();
void test2();
