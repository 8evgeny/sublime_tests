

#include <cstdlib> 
#include <iostream>
using namespace std;
 
int main()
{
 setlocale(LC_ALL, "rus");
 
 int sizeOfArray = 0; // размер массива (введет пользователь)
 
 cout << "To create array input your size: ";
 cin >> sizeOfArray;
 
 // ВНИМАНИЕ! int* arrWithDigits - объявление указателя
 // на участок памяти, которую выделит new
 int* arrWithDigits = new int [sizeOfArray];  //Динамический массив - память будет выделена 
 // в соответствии с введенным значением !!!!
 
 for (int i = 0; i < sizeOfArray; i++)
 {
 arrWithDigits[i] = i + 1;
 cout << arrWithDigits[i] << " ";
 } 
 cout << endl;
 
 delete [] arrWithDigits; // освобождение памяти
 
 system( "PAUSE" ) ; return 0 ;
 
}