#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	
	setlocale(LC_CTYPE, "rus");

	string str = "�������� ���������� ���� � 5-�� �������.";

	int maxAttempt = 5;		// ���������� ���������� �������
	int attempt = 0;		// ����� ������� �������
	string color = "red";	// ��������� ����

	while (attempt < maxAttempt) {
		attempt++;
		cout << str << " ������� " << attempt << endl;
		string value = "";
		cin >> value;

		if (value == "") 
		{
			break;
		}
		if (value != color)
		{
			str = "�� �� �������!";
			continue;
		}

		cout << "�����������, �� ������� � " << attempt << " �������!" << endl;
		break;
	}
	
	system("pause");
	return 0;
}
