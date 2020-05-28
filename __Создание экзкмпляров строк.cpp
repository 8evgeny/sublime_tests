#include <string>
#include <iostream>
#include <conio.h>
using namespace std;

int main ()
{

const char* constCStyleString = "Hello String!";
cout << "Constant string is: " << constCStyleString << endl;

std::string strFromConst (constCStyleString); // Конструктор
cout << "strFromConst is: " << strFromConst << endl;

std::string str2 ("Hello String!");
std::string str2Copy (str2);
cout << "str2Copy is: " << str2Copy << endl;

// Инициализировать строку первыми 5 символами другой строки
std::string strPartialCopy (constCStyleString, 5);
cout << "strPartialCopy is: " << strPartialCopy << endl;

// Инициализировать строку 10 символами 'a'
std::string strRepeatChars (10, 'a');
cout << "strRepeatChars is: " << strRepeatChars << endl;


getch(); 
return 0;
}
// Constant string is: Hello String!
// strFromConst is: Hello String!
// str2Copy is: Hello String!
// strPartialCopy is: Hello
// strRepeatChars is: aaaaaaaaaa

