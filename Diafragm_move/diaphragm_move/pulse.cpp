#include "diaphragm.h"
#define DELAY delay(5)
#define INTERSECT delay(2)
void pulse1() {
  digitalWrite(GPIO35, HIGH);
  digitalWrite(GPIO33, LOW);
  digitalWrite(GPIO36, LOW);
  digitalWrite(GPIO32, LOW);
  DELAY;
  sleep();
}
void pulse2() {
  digitalWrite(GPIO35, HIGH);
  digitalWrite(GPIO33, HIGH);
  digitalWrite(GPIO36, LOW);
  digitalWrite(GPIO32, LOW);
  INTERSECT;
  sleep();
}
void pulse3() {
  digitalWrite(GPIO35, LOW);
  digitalWrite(GPIO33, HIGH);
  digitalWrite(GPIO36, LOW);
  digitalWrite(GPIO32, LOW);
  DELAY;
  sleep();
}
void pulse4() {
  digitalWrite(GPIO35, LOW);
  digitalWrite(GPIO33, HIGH);
  digitalWrite(GPIO36, HIGH);
  digitalWrite(GPIO32, LOW);
  INTERSECT;
  sleep();
}
void pulse5() {
  digitalWrite(GPIO35, LOW);
  digitalWrite(GPIO33, LOW);
  digitalWrite(GPIO36, HIGH);
  digitalWrite(GPIO32, LOW);
  DELAY;
  sleep();
}
void pulse6() {
  digitalWrite(GPIO35, LOW);
  digitalWrite(GPIO33, LOW);
  digitalWrite(GPIO36, HIGH);
  digitalWrite(GPIO32, HIGH);
  INTERSECT;
  sleep();
}
void pulse7() {
  digitalWrite(GPIO35, LOW);
  digitalWrite(GPIO33, LOW);
  digitalWrite(GPIO36, LOW);
  digitalWrite(GPIO32, HIGH);
  DELAY;
  sleep();
}
void pulse8() {
  digitalWrite(GPIO35, HIGH);
  digitalWrite(GPIO33, LOW);
  digitalWrite(GPIO36, LOW);
  digitalWrite(GPIO32, HIGH);
  INTERSECT;
  sleep();
}
void test() {
  digitalWrite(GPIO32, HIGH);
  digitalWrite(GPIO33, HIGH);
  digitalWrite(GPIO35, HIGH);
  digitalWrite(GPIO36, HIGH);
  delay(500);
  digitalWrite(GPIO32, LOW);
  digitalWrite(GPIO33, LOW);
  digitalWrite(GPIO35, LOW);
  digitalWrite(GPIO36, LOW);
  delay(500);
}
void sleep(){
//    digitalWrite(GPIO32, LOW);
//    digitalWrite(GPIO33, LOW);
//    digitalWrite(GPIO35, LOW);
//    digitalWrite(GPIO36, LOW);
//    delay(0);
  }
