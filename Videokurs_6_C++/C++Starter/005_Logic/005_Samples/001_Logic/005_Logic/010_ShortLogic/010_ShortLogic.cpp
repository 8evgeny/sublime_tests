// 009_ShortLogic.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int minValue = 1;
	int denominator = 0;
	int item = 2;

	// �������, ������� �������� � �������������� ������� ����������������� ����������.
	// ���� �� ��� ��������� ����������� ���������, �� �������� ������� �� ������ ��������, 
	// ������������ �� ������ ������� �� 0.

	if ((item / denominator) > minValue && (denominator != 0)) // �������� ���� �������� &
	{
		cout << "Block IF" << endl;
	}
	else
	{
		cout << "Block ELSE" << endl;
	}

	return 0;
}

