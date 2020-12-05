#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int *pAge = new int[10];

	pAge[0] = 10;
	pAge[1] = 20;

	cout << "First element - " << pAge[0] << ", second element - " << pAge[1] << endl;

	delete pAge;

	system("pause");
	return 0;
}
