#include "stdafx.h"
#include <iostream>

using namespace std;

int GetSum(int *arr, int count);

int main()
{
	int size = 50;
	int *arr = new int[size];

	for (int i = 0; i < 50; i++)
	{
		*(arr + i) = rand();
	}

	int sum = GetSum(arr, size);

	cout << "Total sum of the array equals = " << sum << endl;

	system("pause");
	return 0;
}

int GetSum(int *arr, int count) 
{
	int total = 0;
	for (int i = 0; i < count; i++)
	{
		total += *(arr + i);
	}

	return total;
}

