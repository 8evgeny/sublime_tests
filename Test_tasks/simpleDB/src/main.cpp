#include "simpleDB.h"
using namespace std;

int main(int argc, char** argv) {

 int oper = 0;
 cout<<"Введите операцию:\n";
 cout<<"1 - отображение существующих записей:\n";
 cout<<"2 - ввод новых данных:\n";
 cin>>oper;
 if(oper == 1) readDB();
 if(oper == 2) input_new_data();
 if((oper!=1)&&(oper!=2)){cout<<"Ошибка ввода\n";return 1;}

 cout<<"Далее\n";
return 0;
}




