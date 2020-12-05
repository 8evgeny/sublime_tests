#include "stdafx.h"
#include <iostream>

using namespace std;

void TestFunc(int a = 5, int b = 10);

int main()
{
	int operator1 = 2, operator2 = 3;

	TestFunc(operator1, operator2);
	TestFunc(operator1);
	TestFunc();

    return 0;
}

void TestFunc(int a, int b)
{
	cout << "a = " << a << "; b = " << b << endl;
}
