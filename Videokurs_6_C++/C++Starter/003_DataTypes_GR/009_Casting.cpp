#include "stdafx.h"
#include <iostream>

using namespace std;
// C++ ����������� �������� �� ����� ������������ �������� ������ ���� ����������, ����������� � ������� ����;
// �++ ����������� �������� ��� �������������� ������ ����� � ����������;
// �++ ����������� �������� ��� �������� ���������� ��������.

int main()
{
	float a = 3;			// ��� int ������������� � float
	cout << a << endl;
	
	int b = 3.145f;			// ��� float ������������� � int 
	cout << b << endl;

	int c = 7.2E12;			// �������� �� �����������
	cout << c << endl;

	int x = 100;

	//char d1 = { 31325 };	// ������� �� ����������� 
	// cout << d1;			// ������

	char d2 = { 66 };		// ���������, ��������� �������� 66 ������ � ���������� �������� �������� ���� char

	char d3 = x;			// ���� ������ ������������� ���������
	char d4 { x };			// �� ���������

	// ��������
	cin.get();
    return 0;
}
