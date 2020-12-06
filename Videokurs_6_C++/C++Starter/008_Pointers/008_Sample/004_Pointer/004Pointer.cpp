#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int a = 10;
	int b = 15;

	cout << "Value of variable a: " << a << endl;
	cout << "Value of variable b: " << b << endl;

	int *pointer = &a;

	cout << "Pointer = 0x" << pointer << endl;
	cout << "*Pointer = " << *pointer << endl;

	pointer = &b;

	cout << "Pointer of b = 0x" << pointer << endl;
	cout << "*Pointer of b = " << *pointer << endl;

	system("pause");
	return 0;
}
