#include "main.h"
//Добавить Абхиджит накшатру
#include "nativ.h"
using namespace std;

int main(int argc, char** argv) {
  int n;
  if (argc == 1) {
    n = 0;
  } else {
    n = stoi(argv[1]);
  }
  nativ curr_Time(n);
  nativ my("Evgeny");
  nativ t("Танюша");
  nativ d1("Stasya");
  nativ d2("Taya");
  nativ d3("Maya");
  nativ d4("Ulyana");

  //  muhurta mux;
  //  muhurta my_mux(my);

  //  thread t2([&]() {  // Передаем все переменные
  //    result = curr_Time.Qtvara(argc, argv);
  //  });

  //  thread t1(&nativ::Qtvara, ref(curr_Time));
  //  thread t2(&nativ::Qtvara, ref(t));
  cout << "navatara: " << my.name << " " << my.navatara(curr_Time) << endl;
  string navatara = my.navatara(curr_Time);
  curr_Time.qtPanchang(my, navatara);
  //  t1.join();
  //  t2.join();

  return 0;
}

// swedll.h:339:1: error: '__declspec' attributes are not enabled; use
// '-fdeclspec' or '-fms-extensions' to enable support for __declspec attributes
// swedll.h:74:30: note: expanded from macro 'DllImport'
