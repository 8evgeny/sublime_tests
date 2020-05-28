#include <string>
#include <iostream>
#include <conio.h>
int main ()
{
using namespace std;
// Пример строки
string strSTLString ("Hello String");

// Доступ к содержимому строки с использованием
// синтаксиса массива
cout<<"Displaying the elements in the string using array-syntax:"
<< endl;
for ( size_t nCharCounter = 0
; nCharCounter < strSTLString.length ()
; ++ nCharCounter )
{
cout << "Character [" << nCharCounter << "] is: ";
cout << strSTLString [nCharCounter] << endl;
}
cout << endl;


// Доступ к содержимому строки с использованием итератора
cout << "Displaying the contents of the string using iterators: "
<< endl;
int charOffset = 0;
string::const_iterator iCharacterLocator;
for ( iCharacterLocator = strSTLString.begin ()
; iCharacterLocator != strSTLString.end ()
; ++ iCharacterLocator )
{
cout << "Character [" << charOffset ++ << "] is: ";
cout << *iCharacterLocator << endl;
}
cout << endl;


// Обращение к содержимому строки в стиле С
cout << "The char* representation of the string is: ";
cout << strSTLString.c_str () << endl;


getch(); 
return 0;
}


