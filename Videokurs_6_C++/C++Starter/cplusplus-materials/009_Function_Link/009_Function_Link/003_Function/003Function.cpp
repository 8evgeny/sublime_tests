#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

void Operation(string val1 = "val", int val2 = 10, double val3 = 12.2);

int main()
{
	Operation();                  // 1-я перегрузка.
	Operation("val");             // 2-я перегрузка.
	Operation("val", 10);         // 3-я перегрузка. 
	Operation("val", 10, 12.2);   // 4-я перегрузка.


	system("pause");
	return 0;
}
void Operation(string val1, int val2, double val3)
{
	cout << val1 << " " << val2 << " " << val3 << endl;
}
