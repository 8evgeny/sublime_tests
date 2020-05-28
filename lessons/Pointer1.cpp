

#include <cstdlib> 
#include <iostream>
using namespace std;
 
int main()
{
 setlocale(LC_ALL, "rus");
 
 const int SizeOfArray = 5000;
 int arrWithDigits[SizeOfArray] = {};
 cout << "Array in memory " << sizeof(arrWithDigits) << " byts" << endl;
 
 int amount = 0;
 cout << "How many numbers you input in array? ";
 cin >> amount;
 cout << "Realy nesessary " << amount * sizeof(int) << " byte" << endl;
 
 for (int i = 0; i < amount; i++)
 {
 cout << i + 1 << "-number: ";
 cin >> arrWithDigits[i];
 }
 cout << endl;
 
 for (int i = 0; i < amount; i++)
 {
 cout << arrWithDigits[i] << "  ";
 }
 cout << endl;
 
 system( "PAUSE" ) ; return 0 ;
 
}