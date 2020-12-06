#include "stdafx.h"
#include <iostream>

using namespace std;

void add(int, int, int &);

int main()
{
	int a = 0;
	cout << "Enter first number: " << endl;
	cin >> a;

	int b = 0;
	cout << "Enter second number: " << endl;
	cin >> b;

	int sum = 0;
	add(a, b, sum);

	cout << a << " + " << b << " = " << sum << endl;

	system("pause");
	return 0;
}

void add(int x, int y, int &sum)
{
	sum = x + y;
}