#include "stdafx.h"
#include <iostream>
#include "example.h"

using namespace std;

int main()
{
	int someValue = GetValue();

	cout << someValue << endl;

	system("pause");
	return 0;
}

int GetValue()
{
	return 10;
}
