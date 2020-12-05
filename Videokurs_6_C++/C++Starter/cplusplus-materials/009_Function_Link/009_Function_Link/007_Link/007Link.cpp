#include "stdafx.h"
#include <iostream>
// Ссылки представляют собой "псевдонимы" для переменных и позволяют работать с данными через ссылку не по копии а по значению.
using namespace std;

int main()
{
	int a = 10;

	cout << "Variable a = " << a << endl;

	// Создаем ссылку на переменную типа int
	int &b = a;

	cout << "Variable a = " << b << endl;
	cout << "Change variable b" << endl;

	b = 15;

	cout << "Variable a = " << a << endl;
	cout << "Variable a = " << b << endl;

	// int &c; // Не допустимо! При объявлении ссылочную переменную необходимо инициализировать.

	system("pause");
	return 0;
}

