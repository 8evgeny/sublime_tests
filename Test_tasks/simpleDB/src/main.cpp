#include "simpleDB.h"
using namespace std;

int main(int argc, char** argv) {
//не просматривает и не редактирует последнюю запись

 string oper ="0";
 while(1){
  cout<<"Введите операцию:\n"<<
        "1 - список всех данных:\n"<<
        "2 - просмотр записи:\n"<<
        "3 - новая запись:\n"<<
        "4 - редактирование записи:\n"<<
        "5 - завершить работу:\n";
  cin>>oper;
  regex regexpr ("[12345]");
  if (regex_match (oper,regexpr)) {
  if(oper == "1") read_data();
  if(oper == "2") view_data();
  if(oper == "3") input_data();
  if(oper == "4") edit_data();
  if(oper == "5") return 0;
  } else cout<<"Повторите ввод\n\n";
 }

}




