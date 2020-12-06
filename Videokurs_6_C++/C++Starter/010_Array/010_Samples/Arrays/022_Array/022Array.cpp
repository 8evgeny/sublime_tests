#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int arr1[5] = { 1, 2, 3, 4, 5 }; // Допустипо указывать не все эдементы
	int arr2[100] = { 0 };			 //  Массив инициализируется нулями

	double arr3[4] { 3.14, 2.18, 89.32, 12.45 };	// C++11

	// Не допускается инициализация массива элементами разных типов

	// int arr4[3] = { 50, "Hello", 3.24 };

	system("pause");
    return 0;
}

