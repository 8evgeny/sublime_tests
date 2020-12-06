#include "stdafx.h"
#include <iostream>

using namespace std;

void add_two(int);

int main()
{
	int a = 0;
	cout << "Enter the value: " << endl;
	cin >> a;

	cout << "Value of variable a = " << a << endl;

	add_two(a);

	cout << "Value of variable a = " << a << endl;

	system("pause");
	return 0;
}

void add_two(int a)
{
	a = a + 2;
	cout << "Value int a = " << a << endl;
}