#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int *pAge = new int;

	cout << "Enter your age: ";
	cin >> *pAge;

	cout << "Age " << *pAge << " is stored at 0x" << pAge << endl;

	delete pAge;

	pAge = 0;

	system("pause");
	return 0;
}
