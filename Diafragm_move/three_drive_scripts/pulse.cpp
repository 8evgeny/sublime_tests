#include "uln2003.h"
void Pulse::delay(int ms){
    std::chrono::milliseconds pause{ms};
    std::this_thread::sleep_for(pause);
}
void Pulse::pulse1(int a,int b, int c,int d) {
  GPIO_HIGH(a);
  GPIO_LOW(b);
  GPIO_LOW(c);
  GPIO_LOW(d);
  DELAY
}
void Pulse::pulse2(int a,int b, int c,int d) {
  GPIO_HIGH(a);
  GPIO_HIGH(b);
  GPIO_LOW(c);
  GPIO_LOW(d);
  INTERSECT
}
void Pulse::pulse3(int a,int b, int c,int d) {
  GPIO_LOW(a);
  GPIO_HIGH(b);
  GPIO_LOW(c);
  GPIO_LOW(d);
  DELAY
}
void Pulse::pulse4(int a,int b, int c,int d) {
  GPIO_LOW(a);
  GPIO_HIGH(b);
  GPIO_HIGH(c);
  GPIO_LOW(d);
  INTERSECT
}
void Pulse::pulse5(int a,int b, int c,int d) {
  GPIO_LOW(a);
  GPIO_LOW(b);
  GPIO_HIGH(c);
  GPIO_LOW(d);
  DELAY
}
void Pulse::pulse6(int a,int b, int c,int d) {
  GPIO_LOW(a);
  GPIO_LOW(b);
  GPIO_HIGH(c);
  GPIO_HIGH(d);
  INTERSECT
}
void Pulse::pulse7(int a,int b, int c,int d) {
  GPIO_LOW(a);
  GPIO_LOW(b);
  GPIO_LOW(c);
  GPIO_HIGH(d);
  DELAY
}
void Pulse::pulse8(int a,int b, int c,int d) {
  GPIO_HIGH(a);
  GPIO_LOW(b);
  GPIO_LOW(c);
  GPIO_HIGH(d);
  INTERSECT
}
void Pulse::sleep(int a,int b, int c,int d) {
  GPIO_LOW(a);
  GPIO_LOW(b);
  GPIO_LOW(c);
  GPIO_LOW(d);
  SLEEP
}




