#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "rus");

	int number = 0;		// �����, ��������� �������� ���������� ��������
	int factorial = 1;	// ���������

	cout << "������� �����: ";
	cin >> number;

	cout << "��������� �����: " << number << "! = ";

	do
	{
		if (number == 0)
		{
			factorial = 1;
			break;
		}
		factorial = factorial * number;
		number--;

	} while (number > 0);
	
	cout << factorial << endl;
	
	system("pause");
	return 0;
}
