#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

int Mul(int x, int y);

int main()
{
	int val1 = 0, val2 = 0, result;

	cout << "Enter the number and the degree of the number in space or Enter: ";
	cin >> val1 >> val2;

	result = Mul(val1, val2);

	cout << val1 << " * " << val2 << " = " << result << endl;

	system("pause");
	return 0;
}

int Mul(int x, int y)
{
	int temp = x * y;
	return temp;
}
