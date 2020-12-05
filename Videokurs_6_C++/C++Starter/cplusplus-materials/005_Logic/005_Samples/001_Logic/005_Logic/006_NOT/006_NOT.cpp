#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	bool a = false;		// 1

	bool result = !a;

	cout << boolalpha << result << endl;
	
	/* **************************************** */

	int b = 1;			// 0000 ... 0000 0001

	int c = ~b;			// 1111 ... 1111 1110 = -2

	cout << c << endl;

	/* Изменение знака числа */
	// Что бы изменить знак числа, необходимо инвертировать каждый бит числа и прибавить единицу 
	
	b = 1;

	c = ~b;
	c = c + 1;

	cout << c << endl;

	return 0;
}