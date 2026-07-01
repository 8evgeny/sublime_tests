#include <iostream>
using namespace std;

int main()
{
   // Request LOTS of memory space, use nothrow
   int* pointsToManyNums = new(nothrow) int [0x1fffffffFF];

   if (pointsToManyNums) // check pointsToManyNums != NULL
   {
      cout << "Memory allocation OK. Ending program" << endl;
      // Use the allocated memory 
      delete[] pointsToManyNums;
   }
   else 
      cout << "Memory allocation failed. Ending program" << endl;

   return 0;
}
