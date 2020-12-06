#include "stdafx.h"
#include <iostream>

using namespace std;
// Если аргументом функции является массив, его можно обьявить тремя способами

void func1(int *p_arr)	// Указатель
{ 
}

void func2(int arr[10])	// Массив фиксированного размера
{ 
}

void func3(int arr[])	// Массив не определенного размера
{
}

int main()
{
	system("pause");
	return 0;
}
