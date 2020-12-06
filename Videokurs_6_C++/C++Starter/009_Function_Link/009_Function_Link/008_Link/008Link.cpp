#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int a = 10;
	int *p_a = &a;
	int &l_a = a;

	cout << "Value of variable: a = " << a << "; p_a = " << *p_a << " (" << p_a << "); l_a = " << l_a << endl;

	*p_a = 13;
	cout << "Value of variable: a = " << a << "; p_a = " << *p_a << " (" << p_a << "); l_a = " << l_a << endl;

	l_a = 15;
	cout << "Value of variable: a = " << a << "; p_a = " << *p_a << " (" << p_a << "); l_a = " << l_a << endl;

	system("pause");
	return 0;
}

