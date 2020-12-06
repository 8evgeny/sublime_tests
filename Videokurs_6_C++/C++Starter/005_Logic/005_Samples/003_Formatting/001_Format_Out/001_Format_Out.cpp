#include "stdafx.h"
#include <iostream>

#include <ctime>

using namespace std;

int main()
{
	cout.width(80);							// задает ширину поля	
	cout.fill('*');							// устанавливает символ заполнитель, по умолчианию символ заполнитель - пробел

	cout << left << "Hello, Vladimir!" << endl;
		
	// по умолчанию точность равна 6
	cout << fixed;		// манипулятор показывает, что установленная точность относится к количеству знаков после запятой
	cout.precision(3);  // задает количество знаков после десятичной точки

	cout << 3.31456473 << endl;

    return 0;
}

