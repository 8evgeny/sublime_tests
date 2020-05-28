#include <iostream>
#include <string>
#include <vector>
#include <locale.h>
#include <algorithm>
#include <conio.h>
using namespace std;

#include <string.h>
#include <windows.h>
	
//setlocale (LC_ALL, "Rus");
ostream& operator << (ostream& stream, char* rout)
{
char* tmp;
tmp = new char[strlen(rout) + 1];
CharToOem(rout, tmp);
stream.write(tmp, strlen(tmp));
delete [] tmp;
return stream;
}

int main()
{
cout << "Русский текст";



 getch(); // Ожидаем символ

 return 0;   
}  
