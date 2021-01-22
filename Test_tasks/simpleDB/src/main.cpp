#include "simpleDB.h"
using namespace std;

int main(int argc, char** argv) {

 unsigned char oper ;
 cout<<"Введите операцию:\n";
 cout<<"1 - отображение существующих записей:\n";
 cout<<"2 - ввод новых данных:\n";

 while(1){
  cin>>oper;
  if(oper == '1') {readDB();break;}
  if(oper == '2') {input_data();break;}
  if((oper!=1)&&(oper!=2)) cout<<"Повторите ввод\n";
  }





 cout<<"Далее\n";
return 0;
}




