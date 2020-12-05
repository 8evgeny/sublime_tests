#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int a = 8;				// 0000 ... 0000 0000  0000 1000
	int b = a >> 1;			// 0000 ... 0000 0000  0000 0100
	int c = a << 1;			// 0000 ... 0000 0000  0001 0000
	c = c << 1;
	cout << "a = " << a << endl;
	cout << "a >> 1 = " << b << endl;
	cout << "a << 1 = " << c << endl;

	return 0;
}