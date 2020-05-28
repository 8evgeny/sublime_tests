#include <cstdlib> 
#include <iostream>
using namespace std;
 
int main()
{
 
 int a = 5;
 int *pa = &a;   // !!!!! Указатель на переменную
 int &aref =a;  // !!!!! Cсылка на переменную
 // ссылка хранит адрес переменной, но с ней можно работать так-же 
 //как с самой переменной

cout<< "pa\t"<<pa<<endl;
cout<< "*pa\t"<<*pa<<endl;
cout<< "aref\t"<<aref<<endl; //!!!
// Арифметика указателей
cout<< "pa\t"<<pa<<endl;
cout<< "*pa\t"<<*pa<<endl;
pa++;
cout<< "pa+4\t"<<pa<<endl;      //Доступ к чужим данным
cout<< "*(pa+4)\t"<<*pa<<endl;  
pa++;
cout<< "pa+8\t"<<pa<<endl;      //Доступ к чужим данным
cout<< "*(pa+8)\t"<<*pa<<endl;

cout<< "aref\t"<<aref<<endl; //!!!
aref++;
cout<< "aref\t"<<aref<<endl; //!!! Для ссылок арифметики указателей нет 
// aref++ увеличивает на 1 саму переменную

cout<< "aref\t"<<aref<<endl;

aref = aref + 3  ;

cout<< "aref\t"<<aref<<endl;

aref = 55;                 // !!!!!!!!!!!!!!!!!
cout<< "a\t"<<a<<endl;

int *ppa = &aref;
// !! - В указателе ppa хранится адрес ссылки а в ссылке хранится 
//адрес переменной а

*ppa = 12; //  !!!!!!!!!!!! Мы изменили переменную через цепочку - ppa - aref 
cout<< "a\t"<<a<<endl;
 // system( "PAUSE" ) ; return 0 ;
 }