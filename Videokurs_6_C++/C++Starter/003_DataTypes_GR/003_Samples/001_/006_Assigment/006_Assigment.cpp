#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	// Для целых типов не происходит преобразование типа результата арифметических операций

	// Присвоение со сложением
	int operand1 = 10;
	operand1 = operand1 + 5;
	operand1 += 5;				// краткая форма записи

	// присвоение с вычитанием 
	int operand1 = 10;
	operand1 = operand1 - 5;
	operand1 -= 5;


	// присвоение с умножением
	int operand1 = 10;
	operand1 = operand1 * 5;
	operand1 *= 5;


	// присвоение с делением
	int operand1 = 10;
	operand1 = operand1 / 5;
	operand1 /= 5;

	// присвоение с получением остатка от деления
	int operand1 = 10;
	operand1 = operand1 % 5;
	operand1 %= 5;
	
	// Для вещественных типов не происходит преобразование типа результата арифметических операций

	// присвоение с делением
	double operand2 = 3;
	operand2 = operand2 / 2;
	operand2 /= 2;

	// присвоение с делением
	float operand3 = 7;
	operand3 = operand3 / 3;
	operand3 /= 3;

	// Задержка
	cin.get();
	return 0;
}

