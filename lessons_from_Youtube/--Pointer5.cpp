
#include <cstring>
#include <cstdlib> 
#include <iostream>
using namespace std;
 
char* giveNewMem(char *pstr1, int reqSize);
 
int main()
{
 setlocale(LC_ALL, "rus");
 
 int strSize1 = strlen("строка 1 ") + 1;
 int strSize2 = strlen("+ строка 2") + 1;
 
 char* pStr1 = new char[strSize1];
 strcpy (pStr1, strSize1, "строка 1 ");
 
 char* pStr2 = new char[strSize2];
 strcpy_s(pStr2, strSize2, "+ строка 2");
 
 cout << "1)" << pStr1 << endl;
 cout << "2)" << pStr2 << endl << endl;
 
 cout << "pStr1 занимает " << strSize1 << " байт памяти c \\0" << endl;
 cout << "pStr2 занимает " << strSize2 << " байт памяти c \\0" << endl;
 
 // strcat_s(pStr1, strSize1, pStr2); // НЕПРАВИЛЬНО! НЕДОСТАТОЧНО ПАМЯТИ В pStr1
 
 int requiredSize = (strSize1 + strSize2) - 1;
 cout << "\nНеобходимо " << requiredSize << " байт памяти для объединения строк." << endl << endl;
 
 pStr1 = giveNewMem(pStr1, requiredSize); //функция, которая перевыделит память
 
 strcat (pStr1, requiredSize, pStr2);
 cout << "pStr1: " << pStr1 << endl << endl;
 
 delete[] pStr1; // освобождаем память, которая была перевыделена в функции для strInFunc 
 delete[] pStr2; // освобождаем память, которая была выделена в main 
 
system( "PAUSE" ); return 0;

}
 
char* giveNewMem(char *pstr1, int reqSize) // !!! Функция возвращает указатель
{
 char* strInFunc = new char[reqSize]; // для копирования строки pstr1 перед удалением памяти
 
 strcpy (strInFunc, reqSize, pstr1);
 
 delete [] pstr1; // освобождаем память pstr1
 
 return strInFunc;
}