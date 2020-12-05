#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int a = 10;

	int *const pA = &a;

	// Данные на которые указывает указатель изменять допустимо.
	*pA = 11;

	cout << "Address : " << pA << ", value = " << *pA << endl;

	int b = 12;

	// Нельзя изменить адрес, хранящийся в указателе.
	// pA = &b;

	system("pause");
	return 0;
}
