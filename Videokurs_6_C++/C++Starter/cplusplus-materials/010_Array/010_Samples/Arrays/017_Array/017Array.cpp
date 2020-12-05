#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	// на 9-й строке создаем массив указателей размерностью в 3 элемента
	int *arr_pointers[3];

	int x = 100, y = 200, z = 300;

	*arr_pointers = &x;
	*(arr_pointers + 1) = &y;
	*(arr_pointers + 2) = &z;
	cout << &x << endl;
	// Выводим значения массива
	for (int i = 0; i < 3; i++)
	{
		cout << i + 1 << " value in array = " << *(arr_pointers + i) << endl;
	}

	cout << "--------------------------------------------------" << endl;

	// Выводим значения хранящиеся по адресам находящимся в массиве
	for (int i = 0; i < 3; i++)
	{
		cout << i + 1 << " value = " << *(*(arr_pointers + i)) << endl;
	}


	system("pause");
	return 0;
}

