#include "stdafx.h"
#include <iostream>

using namespace std;

void recursion(int counter);

int main()
{
	recursion(3);

	system("pause");
	return 0;
}

void recursion(int counter)
{
	counter--;

	cout << "First part of recursion function " << counter << endl;

	if (counter != 0)
	{
		recursion(counter);
	}
	cout << "Second part of recursion function " << counter << endl;
}