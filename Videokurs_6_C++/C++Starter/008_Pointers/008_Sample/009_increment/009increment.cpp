#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "Enter the integer number: ";
	int count = 0;
	cin >> count;

	int *block = new int[count];
	int *pBlock = block;

	cout << "Fill the block: " << endl;

	for (int i = 0; i < count; i++)
	{
		cout << "Enter number: ";
		cin >> *(block + i);
	}

	cout << "Display all numbers in block: " << endl;
	for (int i = 0; i < count; i++)
	{
		cout << *(pBlock++) << " ";
	}
	cout << endl;

	delete[] block;

	system("pause");
	return 0;
}
