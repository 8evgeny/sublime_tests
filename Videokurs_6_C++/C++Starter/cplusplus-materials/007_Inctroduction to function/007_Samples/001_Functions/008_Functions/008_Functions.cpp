#include "stdafx.h"
#include <iostream>

using namespace std;

bool Or(bool a, bool b);

int main()
{
	bool result = false, v1 = true, v2 = false;

	result = Or(v1, v2);

	cout << "a || b = " << result << endl;

	system("pause");
	return 0;
}

bool Or(bool a, bool b)
{
	return a || b;
}