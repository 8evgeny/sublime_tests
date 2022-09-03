#include "main.h"
//Добавить Абхиджит накшатру
#include "nativ.h"
using namespace std;

int main(int argc, char** argv)
{
    int n;
    if (argc == 1) {
        n = 0;
    } else {
        n = stoi(argv[1]);
    }
    nativ curr_Time(n);
    nativ my("Evgeny");
//        nativ t("Танюша");
    //    nativ d1("Stasya");
    //    nativ d2("Taya");
    //    nativ d3("Maya");
    //    nativ d4("Ulyana");
    //    nativ nat("Наташа");
    //  muhurta mux;
    //  muhurta my_mux(my);

    //  thread t2([&]() {  // Передаем все переменные
    //    result = curr_Time.Qtvara(argc, argv);
    //  });

    //  thread t1(&nativ::Qtvara, ref(curr_Time));
    //  thread t2(&nativ::Qtvara, ref(t));

        curr_Time.scanHairCut(my, 60);
    //    curr_Time.scanHairCut(d2, 60);
    //    curr_Time.scanHairCut(d3, 60);
 //   curr_Time.scanHairCut(my, 60);
    //  t1.join();
    //  t2.join();
  //  curr_Time.qtPanchang(my);
    return 0;
}

// swedll.h:339:1: error: '__declspec' attributes are not enabled; use
// '-fdeclspec' or '-fms-extensions' to enable support for __declspec attributes
// swedll.h:74:30: note: expanded from macro 'DllImport'
