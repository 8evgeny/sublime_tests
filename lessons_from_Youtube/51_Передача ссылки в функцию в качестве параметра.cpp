#include <cstdlib> 
#include <iostream>
using namespace std;
 
void Foo (int a) //передача параметра по значению
{
a = 1;
}

void Foo2 (int &a)
{
a = 2;  // !!!!!!!!  с ссылками работаем как с данными по значению
}

void Foo3 (int *a)
{
*a = 3;    // !!!!!!!  с указателями требуется разименование
}

int main()
{
 
 int value = 5;
cout<< "value = \t"<<value<<endl;

Foo (value);  // Функция по значению не сработает
cout<< "Foo = "<<endl;
cout<< "value = \t"<<value<<endl;

Foo2 (value);  //Функция возьмет ссылку сама в качестве параметра
cout<< "Foo2 = "<<endl;
cout<< "value = \t"<<value<<endl;

Foo3 (&value);   // Передаваться адрес переменной
cout<< "Foo3 = "<<endl;
cout<< "value = \t"<<value<<endl;

 system( "PAUSE" ) ; return 0 ;
 }