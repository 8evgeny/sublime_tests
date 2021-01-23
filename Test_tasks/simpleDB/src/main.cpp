#include "simpleDB.h"
using namespace std;

int main(int argc, char** argv) {
 char oper ;
 while(1){
  cout<<"Введите операцию:\n";
  cout<<"1 - отображение существующих записей:\n";
  cout<<"2 - ввод новых данных:\n";
  cout<<"3 - завершить работу:\n";
  cin>>oper;
  if((oper!='1')&&(oper!='2')&&(oper!='3')) cout<<"Повторите ввод\n";
  if(oper == '1') readDB();
  if(oper == '2') {input_data();break;}
  if(oper == '3') return 0;
    }





 cout<<"Далее\n";
return 0;
}




