#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	// Создаем массив с именем arr типа int размерностью 3 элемента
	int arr[3];

	arr[0] = 10;
	arr[1] = 20;
	arr[2] = 30;

	// Выводим значение хранящееся в переменной arr
	cout << "Variable arr contains - " << arr << endl;

	// Получаем адресс переменной arr и выводим его в консоль
	cout << "Address of variable arr - " << &arr << endl;

	system("pause");
	return 0;
}

