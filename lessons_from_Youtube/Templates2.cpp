

#include <cstdlib> 
#include <iostream>
using namespace std; 

template <typename T_1, typename T_2>
T_2 findMax(T_1 firstNum, T_2 secondNum)
{
 if (firstNum > secondNum)
 return firstNum;
 else if (secondNum > firstNum)
 return secondNum;
 else
 return 0;
}
 
int main()
{ 
 setlocale(LC_ALL, "rus");
 
 cout << " 255 and 700! More = " << findMax(255, 700) << endl;
 cout << "8.5 and 4.9! More = " << findMax(8.5, 4.9) << endl;
 // ошибки не будет:
 cout << " 100 and 5.1! More = " << findMax(100, 5.1) << endl;

 system( "PAUSE" ) ; return 0 ;
 
}