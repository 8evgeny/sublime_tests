#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	// Динамически выделяем массив для 50-ти элементов типа int
	int *arr = new int[50];

	// Заполняем массив.
	for (int i = 0; i < 50; i++)
	{
		*(arr + i) = (i + 1) * 2;
	}
	
	// Выводим значения элементов массива.
	for (int i = 0; i < 50; i++)
	{
		cout << *(arr + i) << endl;
	}


	system("pause");
	return 0;
}

