#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	int lines = 15;			// ���������� �����
	int symbInLines = 30;	// ���������� �������� � ������
	char symbol = '*';		// ������ 

	for (int i = 1; i <= lines; i++)
	{
		if (i == 1 || i == lines) // 1-� � ��������� ������
		{
			for (int j = 1; j <= symbInLines; j++)
			{
				cout << symbol; // �������� �� ��������
			}
		}
		else // ��� ������ ����� ������ � ��������������
		{
			cout << symbol; // �������� ���� ������
			for (int j = 1; j <= symbInLines - 2; j++)
			{
				cout << ' '; // ������� � ������ (symbInLines - 2) ���
			}
			cout << symbol; // �������� ��� ���� ������
		}
		cout << endl; // ����� ������
	}

	cout << endl;

	system("pause");
	return 0;
}
