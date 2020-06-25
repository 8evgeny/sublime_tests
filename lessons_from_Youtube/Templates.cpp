

#include <cstdlib> 
#include <iostream>
using namespace std; 
/*
Определяя шаблон функции мы использовали зарезервированные слова C++: template и 
typename.   template говорит о том, что сейчас будет определен шаблон. А в угловых 
скобках после  typename  дается условное  имя типу данных. Тут, вместо имени T, можно
присвоить любое (очень желательно корректное) имя. */


template <typename T>
T calcPercent(T number, int percent)
{
 return number * percent / 100;
}
 
int main()
{
 setlocale(LC_ALL, "rus");
 
 cout << "20% from 200:    " << calcPercent(200, 20) << endl;
 cout << "10% from 42.56:  " << calcPercent(42.56, 10) << endl;
 


 system( "PAUSE" ) ; return 0 ;
 
}