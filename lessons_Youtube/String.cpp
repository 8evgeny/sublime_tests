

#include <cstdlib> 
#include <iostream>
using namespace std;
 
/*Хочу обратить ваше внимание на отличие символьной константы (в одинарных 
	кавычках – 'f', '@' ) от строковой константы (в двойных кавычках "f", "@" ). 
Для первой, компилятором C++ выделяется один байт для хранения в памяти. 
Для символа записанного в двойных кавычках, будет выделено два байта памяти 
 для самого символа и для нулевого (добавляемого компилятором). */
 
int main()
{
 setlocale(LC_ALL, "rus");
 char ee = '4';
 char str[12] = {'r','d','f','-','e','a','s',' ','f','t','y','.'};
 
for (int i = 0; i < 12; i++)
 {
cout << str[i];
 	cout << ee;
 }
 cout << endl;
 

 system( "PAUSE" ) ; return 0 ;
 
}