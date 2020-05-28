#pragma once
#include <wiringPi.h>

#include <iostream>

//#define GPIO50 1  //pin12
//#define GPIO54 4  //pin16
//#define GPIO55 5  //pin18
//#define GPIO56 6  //pin22


#define GPIO32 7  //pin7  черный
#define GPIO33 0  //pin11 желтый
#define GPIO35 2  //pin13 белый
#define GPIO36 3  //pin15 красный
//TOKINA  - поменять pin7  и pin 13 местами !!!!!!

void open(int);
void close(int);
void init();
void pulse1();
void pulse2();
void pulse3();
void pulse4();
void pulse5();
void pulse6();
void pulse7();
void pulse8();
void test();
void sleep();
