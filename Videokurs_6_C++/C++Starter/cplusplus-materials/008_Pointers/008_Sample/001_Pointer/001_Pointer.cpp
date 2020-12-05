#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{

	int age = 18;
	double Pi = 3.14;

	cout << "Address of variable age is: 0x" << &age << endl;

	cout << "Address of variable Pi is: 0x" << &Pi << endl;

	system("pause");
    return 0;
}

