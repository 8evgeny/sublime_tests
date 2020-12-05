#include "stdafx.h"
#include <iostream>

using namespace std;

// прототип функции GetValue
int GetValue();

int main()
{
	int value = GetValue();

	cout << value << endl;

	system("pause");
    return 0;
}

int GetValue()
{
	return 10;
}