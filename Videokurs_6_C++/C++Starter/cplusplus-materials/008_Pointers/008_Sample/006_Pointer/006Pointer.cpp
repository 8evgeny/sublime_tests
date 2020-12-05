#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int age = 30;
	double Pi = 3.14;
	char ch = 'Y';

	int *pInt = &age;
	double *pDouble = &Pi;
	char *pCarh = &ch;

	cout << "Sizeof fundamentals types - " << endl;
	cout << "sizeof(int) = " << sizeof(int) << endl;
	cout << "sizeof(double) = " << sizeof(double) << endl;
	cout << "sizeof(char) = " << sizeof(char) << endl;

	cout << "Sizeof pointers to fundamentals types - " << endl;
	cout << "sizeof(pInt) = " << sizeof(pInt) << endl;
	cout << "sizeof(pDouble) = " << sizeof(pDouble) << endl;
	cout << "sizeof(pCarh) = " << sizeof(pCarh) << endl;

	system("pause");
	return 0;
}
