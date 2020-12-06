// 009_ShortLogic.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int minValue = 1;
	int denominator = 0;
	int item = 2;


	// Условие, которое работает с использованием техники КОРОТКОЗАМКНУТОГО ВЫЧИСЛЕНИЯ.
	// Если бы это выражение вычислялось полностью, то операция деления во втором операнде, 
	// генерировала бы ошибку деления на 0.

	if ((denominator != 0) && (item / denominator) > minValue) // Оставьте один оператор &
	{
		cout << "Block IF" << endl;
	}
	else
	{
		cout << "Block ELSE" << endl;
	}

    return 0;
}

