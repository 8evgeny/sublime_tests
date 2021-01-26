#include "simpleDB.h"
using namespace std;

int main(int argc, char** argv) {
//Регулярка для имени
 string oper;
 while(1){
  cout<<"Введите операцию:\n"<<
        "1 - список всех записей:\n"<<
        "2 - просмотр записи:\n"<<
        "3 - создание новой записи:\n"<<
        "4 - редактирование записи:\n"<<
        "5 - удаление записи:\n"<<
        "6 - завершить работу:\n";
  cin>>oper;
  regex regexpr ("[123456]");
  if (regex_match (oper,regexpr)) {
  if(oper == "1") read_data();
  if(oper == "2") view_data();
  if(oper == "3") input_data();
  if(oper == "4") edit_data();
  if(oper == "5") remove_data();
  if(oper == "6") return 0;
  } else cout<<"Повторите ввод\n\n";
 }

}




