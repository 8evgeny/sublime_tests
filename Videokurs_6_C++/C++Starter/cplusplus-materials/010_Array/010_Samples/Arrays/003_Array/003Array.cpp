#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	// Создаем массив arr типа int размерностью в 4 элемента, и в блоке инициализатора, инициализируем элементы массива, соответствующими значениями
	int arr[4] = { 10, 20, 30, 40 };
	
	// получаем количество байт занимаемое массивом в памяти
	cout << "The size of array arr = " << sizeof(arr) << endl;
	// проверяем сколько байт занисает один элемент массива
	cout << "The size of first element of array = " << sizeof(arr[0]) << endl;
	// расчитываем количество элементов массива
	cout << "Array length = " << sizeof(arr) / sizeof(arr[0]) << " element(s)." << endl;

	cout << "-------------------------------------------------------------------------------------" << endl;

	const int size = 10;

	int arr1[size];
	
	cout << "The size of array arr1 = " << sizeof(arr1) << endl;
	cout << "The size of first element of array = " << sizeof(arr1[0]) << endl;

	cout << "Array length = " << sizeof(arr1) / sizeof(arr1[0]) << " element(s)." << endl;
	 
	system("pause");
	return 0;
}

