#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	const int size = 10;
	int arr[size];

	// Заполнение массива
	for (int i = 0; i < size; i++)
	{
		arr[i] = i * 2;
	}

	// Вывод на экран значений массива
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << endl;
	}

	system("pause");
	return 0;
}

