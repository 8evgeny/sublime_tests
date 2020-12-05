#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	short a = 0;
	
	// постфиксный инкремент
	cout << a << endl;
	cout << a++ << endl;	// сначала выводим на экран значение переменной а, а потом увеличиваем значение переменной на единицу
	cout << a << endl;

	cout << endl;

	// префиксный инкремент
	
	cout << a << endl;
	cout << ++a << endl;	// сначала увеличиваем значение переменной а, а затем выводим на экран
	cout << a << endl;

	// Задержка
	cin.get();
    return 0;
}

