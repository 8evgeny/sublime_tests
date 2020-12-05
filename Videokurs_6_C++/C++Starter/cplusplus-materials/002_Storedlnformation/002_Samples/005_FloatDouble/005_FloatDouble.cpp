// 005_FloatDouble.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	float		a = 0.123456789012345678901234567890123456789012345678901234567890F;
	double		b = 0.123456789012345678901234567890123456789012345678901234567890;

	cout.precision(ios::floatfield);
	cout << a << endl << b << endl;

    return 0;
}

