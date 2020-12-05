#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

void SampleFunction();
void Global();

string value = "Global variable!";

int main()
{
	string value = "Local variable in Main!";

	cout << value << endl;

	SampleFunction();

	Global();

	cin.get();
    return 0;
}

void SampleFunction()
{
	string value = "Local variable in SampleFunction!";

	cout << value << endl;
}

void Global()
{
	cout << value << endl;
}