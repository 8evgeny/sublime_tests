#include "stdafx.h"
#include <iostream>

using namespace std;

void ChangeValue(int a, int b);
void ChangeValueWithPointers(int *a, int *b);

int main()
{
	int a = 10, b = 15;

	cout << "Before call functions: a = " << a << ", b = " << b << endl;

	ChangeValue(a, b);

	cout << "After call ChangeValue: a = " << a << ", b = " << b << endl;

	ChangeValueWithPointers(&a, &b);

	cout << "After call ChangeValueWithPointers: a = " << a << ", b = " << b << endl;

	system("pause");
	return 0;
}

void ChangeValue(int a, int b)
{
	int tmp = a;

	a = b;
	b = tmp;
}

void ChangeValueWithPointers(int *a, int *b)
{
	int tmp = *a;

	*a = *b;
	*b = tmp;
}