#include "simpleDB.h"
#include <conio.h>
#include <clocale>
using namespace std;
int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
//    system("chcp 866");
//    SetConsoleCP(866);
//    SetConsoleOutputCP(866);
//Р РµРіСѓР»СЏСЂРєР° РґР»СЏ РёРјРµРЅРё
 string oper;
 while(1){
  cout<<"Введите операцию:\n"<<
        "1 - Все записи:\n"<<
        "2 - Персона:\n"<<
        "3 - input new person:\n"<<
        "4 - edit person:\n"<<
        "5 - delete person:\n"<<
        "6 - exit:\n";
  cin>>oper;
  regex regexpr ("[123456]");
  if (regex_match (oper,regexpr)) {
  if(oper == "1") read_data();
  if(oper == "2") view_data();
  if(oper == "3") input_data();
  if(oper == "4") edit_data();
  if(oper == "5") remove_data();
  if(oper == "6") return 0;
  } else cout<<"repeat input\n\n";
 }

}




