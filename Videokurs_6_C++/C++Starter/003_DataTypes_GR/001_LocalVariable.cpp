#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int a = 4;

	cout << "1. " << a << endl;

	{ 
		int a = 5;
		cout << "2. " << a << endl;
	}

	{
		int a = 6;
		cout << "3. " <<  a << endl;
	}

	// int a = 7;	// недопустимо создавать переменну с уже существующим именем
	
	cin.get();
    return 0;
}

