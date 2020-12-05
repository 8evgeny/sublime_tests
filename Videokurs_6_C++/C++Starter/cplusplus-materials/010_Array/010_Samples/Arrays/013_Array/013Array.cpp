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

	cout << "Address of first element of array = " << &arr[0] << endl;

	int *pArr = arr; // Адрес из переменной arr присваиваем переменной указателю pArr

	cout << "Value of variable pArr = " << pArr << endl;

	// Первый способ получить значение элементов массива через указатель
	cout << "First value = " << *pArr << ". Address = " << pArr << endl;
	cout << "Second value = " << *(pArr + 1) << ". Address = " << pArr + 1 << endl;
	cout << "Third value = " << *(pArr + 2) << ". Address = " << pArr + 2 << endl;


	system("pause");
	return 0;
}

