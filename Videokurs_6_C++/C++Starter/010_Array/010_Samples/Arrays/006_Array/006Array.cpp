#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	// На 9-й строке создаем двумерный массив с именем  arr типа int размерностью 3 на 3 элемента.
	int arr[3][3];


	// Заполняем массив.
	arr[0][0] = 1;
	arr[0][1] = 2;
	arr[0][2] = 3;

	arr[1][0] = 4;
	arr[1][1] = 5;
	arr[1][2] = 6;

	arr[2][0] = 7;
	arr[2][1] = 8;
	arr[2][2] = 9;

	// Выводим значения массива в консоль.
	cout << arr[0][0] << " ";
	cout << arr[0][1] << " ";
	cout << arr[0][2] << endl;

	cout << arr[1][0] << " ";
	cout << arr[1][1] << " ";
	cout << arr[1][2] << endl;

	cout << arr[2][0] << " ";
	cout << arr[2][1] << " ";
	cout << arr[2][2] << endl;

	system("pause");
	return 0;
}

