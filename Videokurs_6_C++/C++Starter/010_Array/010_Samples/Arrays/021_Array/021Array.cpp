#include "stdafx.h"
#include <iostream>

using namespace std;

void print_square(char arr[][50], int size);

int main()
{
	char arr[10][50];
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			arr[i][j] = '*';
		}		
	}

	print_square(arr, 10);

	system("pause");
	return 0;
}

void print_square(char arr[][50], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			cout << arr[i][j];
		}
		cout << endl;
	}
}
