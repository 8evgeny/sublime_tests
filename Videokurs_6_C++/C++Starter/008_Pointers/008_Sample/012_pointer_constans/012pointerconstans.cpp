#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int hour = 12;

	const int *const pHour = &hour;

	// Нельзя изменять данные на которые указывает указатель.
	 *pHour = 24;
	
	int days = 30;
	// Нельзя именять адрес на который указывает указатель.
	// pHour = &days;

	system("pause");
	return 0;
}
