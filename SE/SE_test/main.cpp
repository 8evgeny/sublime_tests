#include "main.h"
//Добавить Абхиджит накшатру
#include "nativ.h"
using namespace std;

int main(int argc, char** argv) {
  nativ curr_Time;
  //  nativ my("Evgeny");
  nativ t("Танюша");
  //  nativ d1("Stasya");
  //  nativ d2("Taya");
  //  nativ d3("Maya");
  //  nativ d4("Ulyana");

  //  muhurta mux;
  //  muhurta my_mux(my);

  //  thread t2([&]() {  // Передаем все переменные
  //    result = curr_Time.Qtvara(argc, argv);
  //  });

  //  thread t1(&nativ::Qtvara, ref(curr_Time));
  //  thread t2(&nativ::Qtvara, ref(t));
  curr_Time.qtPanchang(argc, argv);
  //  t1.join();
  //  t2.join();

  return 0;
}

// swedll.h:339:1: error: '__declspec' attributes are not enabled; use
// '-fdeclspec' or '-fms-extensions' to enable support for __declspec attributes
// swedll.h:74:30: note: expanded from macro 'DllImport'
