#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "rus");

	int number = 0;		// Число, факториал которого необходимо получить
	int factorial = 1;	// Факториал

	cout << "Введите число: ";
	cin >> number;

	cout << "Факториал числа: " << number << "! = ";

	do
	{
		if (number == 0)
		{
			factorial = 1;
			break;
		}
		factorial = factorial * number;
		number--;

	} while (number > 0);
	
	cout << factorial << endl;
	
	system("pause");
	return 0;
}
