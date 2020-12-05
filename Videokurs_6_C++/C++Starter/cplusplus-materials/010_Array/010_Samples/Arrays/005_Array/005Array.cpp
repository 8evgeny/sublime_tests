#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// Вывод на экран значений массива
	for (int i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++)
	{
		cout << arr[i] << endl;
	}

	system("pause");
	return 0;
}

