#include "stdafx.h"
#include <iostream>

using namespace std;

int AddNumbers(int a, int b);
double AddNumbers(double a, double b);

int main()
{
	int  value1 = 2, value2 = 3;

	//double value3 = 12.3;

	double sum = AddNumbers(value1, value2);

	//double dsum = AddNumbers(12.2, 15.3);

	cout << "value1 + value2 = " << sum << endl;

	system("pause");
	return 0;
}

int AddNumbers(int a, int b)
{
	cout << "Function(int a, int b) is called!" << endl;
	return a + b;
}
double AddNumbers(double a, double b)
{
	cout << "Function(double a, double b) is called!" << endl;
	return a + b;
}