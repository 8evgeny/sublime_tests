#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

string Function();

int main()
{
	string value = Function();

	cout << "Hello, " << value << endl;

	system("pause");
	return 0;
}

string Function()
{
	string value = "Admin!";

	return value;
}