#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	// ****** Саst *****
	
	int a = 256;			// 0000 0000  0000 0000  0000 0001  0000 0000

	char b = (char)a;		//									0000 0000

	short c = short(a);		//						 0000 0001  0000 0000

	cout << b << endl << c << endl;

	// Задержка
	cin.get();
	return 0;
}

