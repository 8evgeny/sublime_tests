#include "stdafx.h"
#include <iostream>

using namespace std;

void CallFunction();

int test = 0;

int main()
{
	for (int i = 0; i < 5; i++)
	{
		CallFunction();
	}

	cout << "Function called CallFunction invoked " << test << " times!";

	cin.get();
	return 0;
}

void CallFunction()
{
	test++;
}