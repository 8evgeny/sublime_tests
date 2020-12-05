#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

void Operation();									// 1-я перегрузка.
void Operation(string value);						// 2-я перегрузка.
void Operation(string value1, int value2);			// 3-я перегрузка
void Operation(string val1, int val2, double val3);	// 4-я перегрузка.

int main()
{
	Operation();                  // 1-я перегрузка.
	Operation("val");             // 2-я перегрузка.
	Operation("val", 10);         // 3-я перегрузка. 
	Operation("val", 10, 12.2);   // 4-я перегрузка.

	system("pause");
	return 0;
}

void Operation()
{
	Operation("val", 10, 12.2);
}
void Operation(string value1)
{
	Operation(value1, 10, 12.2);
}
void Operation(string value1, int value2)
{
	Operation(value1, value2, 12.2);
}
void Operation(string val1, int val2, double val3)
{
	cout << val1 << " " << val2 << " " << val3 << endl;
}
