#include "stdafx.h"
#include <iostream>

#include <ctime>

using namespace std;

int main()
{
	cout.width(80);							// ������ ������ ����	
	cout.fill('*');							// ������������� ������ �����������, �� ���������� ������ ����������� - ������

	cout << left << "Hello, Vladimir!" << endl;
		
	// �� ��������� �������� ����� 6
	cout << fixed;		// ����������� ����������, ��� ������������� �������� ��������� � ���������� ������ ����� �������
	cout.precision(3);  // ������ ���������� ������ ����� ���������� �����

	cout << 3.31456473 << endl;

    return 0;
}

