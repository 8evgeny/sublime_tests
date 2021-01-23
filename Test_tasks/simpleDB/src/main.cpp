#include "simpleDB.h"
using namespace std;
//Регулярку даты доработать
int main(int argc, char** argv) {
 string oper;
 while(1){
  cout<<"Введите операцию:\n"<<
        "1 - отображение существующих записей:\n"<<
        "2 - ввод новых данных:\n"<<
        "3 - редактирование данных:\n"<<
        "4 - завершить работу:\n";
  cin>>oper;
  if(oper!="1"||"2"||"3"||"4")  {system("clear");cout<<"Повторите ввод\n\n";}
//  regex regexpr ("[:digit:]");
//  if (regex_match (oper,regexpr)) {
  if(oper == "1") {system("clear");read_data();}
  if(oper == "2") input_data();
  if(oper == "3") edit_data();
  if(oper == "4") return 0;
//    }
//   system("clear"); cout<<"Повторите ввод\n\n";
 }




 cout<<"Далее\n";
return 0;
}




