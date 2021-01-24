#include "simpleDB.h"
using namespace std;
//Регулярку даты доработать

int main(int argc, char** argv) {
 string oper ="0";
 while(1){
  cout<<"Введите операцию:\n"<<
        "1 - отображение существующих записей:\n"<<
        "2 - ввод новых данных:\n"<<
        "3 - редактирование данных:\n"<<
        "4 - завершить работу:\n";
  cin>>oper;
//  if((oper!="1") && (oper!="2")&& (oper!="3")&& (oper!="4")){system("clear");cout<<"Повторите ввод\n\n";}
  regex regexpr ("[1234]");
  if (regex_match (oper,regexpr)) {
  if(oper == "1") read_data();
  if(oper == "2") input_data();
  if(oper == "3") edit_data();
  if(oper == "4") return 0;
  } else cout<<"Повторите ввод\n\n";
 }
}




