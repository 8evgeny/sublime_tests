#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

string Compare(int, int);

int main()
{
	int value1 = 15, value2 = 15;
	string result;

	result = Compare(value1, value2);

	cout << result << endl;

	system("pause");
	return 0;
}

string Compare(int val1, int val2)
{
	string result = "";

	if (val1 < val2)
	{
		result = "Comparison Less Then";
	}
	else if (val1 > val2)
	{
		result = "Comparison Greater Then";
	}
	else
	{
		result = "Comparison Equal";
	}

	return result;
}