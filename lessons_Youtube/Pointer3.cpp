

#include <cstdlib> 
#include <iostream>
using namespace std;
 
 
void changeData(int varForCh1, int varForCh2);
 
int main()
{
 setlocale(LC_ALL, "rus");
 
 int variableForChange_1 = 0;
 int variableForChange_2 = 0;
 
 cout << "variableForChange_1 = " << variableForChange_1 << endl;
 cout << "variableForChange_2 = " << variableForChange_2 << endl;
 cout << endl;
 
 changeData(variableForChange_1, variableForChange_2);
 
 cout << endl;
 cout << "variableForChange_1 = " << variableForChange_1 << endl;
 cout << "variableForChange_2 = " << variableForChange_2 << endl;
 
  system( "PAUSE" ) ; return 0;
}
 
void changeData(int varForCh1, int varForCh2)
/*После выхода из функции значения переменных теряются !!!!!  
Используя указатели, мы можем передавать в функцию адреса переменных. 
Тогда функция получит возможность работать непосредственно с данными переменных 
по адресу. */

{
 cout << "Enter new value first variable : ";
 cin >> varForCh1;
 cout << "Enter new value second variable : ";
 cin >> varForCh2;
}