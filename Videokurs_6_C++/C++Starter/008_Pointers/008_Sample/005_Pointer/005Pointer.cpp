#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int age = 25;
	int *pAge = &age;

	cout << "Age equals " << age << endl;
	cout << "Address of variable age: 0x" << pAge << endl;

	cout << "Enter an age: ";
	cin >> *pAge;

	cout << "New age equals " << age << endl;
	cout << "New value has 0x" << pAge << " address" << endl;

	system("pause");
	return 0;
}

