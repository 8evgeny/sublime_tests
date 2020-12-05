#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int age = 25;

	int *p_age = &age;

	cout << "p_age is at: 0x" << p_age << endl;

	system("pause");
	return 0;
}

