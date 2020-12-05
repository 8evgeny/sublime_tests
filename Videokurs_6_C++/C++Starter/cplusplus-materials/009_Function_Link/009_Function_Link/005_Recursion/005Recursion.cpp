#include "stdafx.h"
#include <iostream>

using namespace std;

void recursion(int counter);
void func(int counter);

int main()
{
	func(3);

	system("pause");
	return 0;
}

void recursion(int counter)
{
	counter--;

	cout << "Forst part of recursion function " << counter << endl;

	if (counter != 0)
	{
		func(counter);
	}
	cout << "Second part of recursion function " << counter << endl;
}

void func(int counter)
{
	cout << "First part of func function " << counter << endl;

	recursion(counter);

	cout << "Second part of func function " << counter << endl;
}