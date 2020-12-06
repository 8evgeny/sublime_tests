#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int a = 20;

	// Данные в указателе изменять нельзя.
	const int *pA = &a;

	cout << pA << endl;

	int b = 30;

	// Можно изменить адрес памяти на который указывает указатель.
	pA = &b;

	cout << pA << endl;

	// Ошибка компиляции, нельзя изменять данные.
	//*pA = 40;

	// Ошибка компиляции, нельзя присвоить константу не константе
	//int *pointer = pA;

	system("pause");
	return 0;
}
