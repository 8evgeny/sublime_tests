

#include <cstdlib> 
#include <iostream>
using namespace std;
 

 
int main()
{
 setlocale(LC_ALL, "rus");
 
 char str[] = "Zil bil pyos"; // '\0' присутствует неявно
 
 cout << str << endl;
 

 system( "PAUSE" ) ; return 0 ;
 
}