#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int a = 10;
	int b = 15;

	int *pointer = &a;

	cout << "*pointer = " << *pointer << endl;

	pointer = &b;

	cout << "*pointer = " << *pointer << endl;

	// Всегда инициализируйте указатели. Непроинициализированные указатели являются источниками ошибок и аварийного завершения программы.
	int *p_void = NULL; // нулевой указатель

	system("pause");
	return 0;
}