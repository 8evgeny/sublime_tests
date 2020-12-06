#include "stdafx.h"
#include <iostream>

using namespace std;

// Константный указатель на константные данные,т.е. ничто не может быть изменено
void CalcArea(const double* const pPi, const double* const pRadius, double* const pArea) 
{
	// проверить указатели перед использованием!
	if (pPi && pRadius && pArea)
		*pArea = (*pPi) * (*pRadius) * (*pRadius);
 }

int main()
{
	const double pi = 3.1416;
	cout << "Enter radius of circle: ";

	double radius = 0;
	cin >> radius;

	double area = 0;

	CalcArea(&pi, &radius, &area);

	cout << "Area is = " << area << endl;

	system("pause");
	return 0;
}