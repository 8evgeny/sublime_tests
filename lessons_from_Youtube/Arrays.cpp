
// в этой программе создаем массив с размером size,
// с помощью цикла for вносим данные во все ячейки
// массива и отображаем их содержимое на экран
#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
 setlocale(LC_ALL, "rus");

 const int SIZE = 10; //объявляем константу
 int firstArray[SIZE] = {}; //объявляем массив с количеством элементов SIZE
 //и инициализируем его нулями

int i = 0;

 while (i < SIZE ) { cout << i<<"-i cell consist "<<firstArray[i]<<endl;
 	i++;
 }
 cout<<"\n"	;
 for (int i = 0; i < SIZE ; i++) //заполняем и отображаем значения на экран
 {
 firstArray[i] = i + 1; // на первом шаге цикла firstArray[0] присвоить 1 (0 + 1)
 cout << i << "-i cell consist " << firstArray[i] << endl;
 }
 cout << endl;

 system( "PAUSE" ) ; return 0 ;

}
