#include "stdafx.h"
#include <iostream>

using namespace std;
/*
		����������� ��� � ��� ���������� ��������, �������� � ������������ ������ ���� ������� ������������� ��������� 
		������������, ���������� ��������� �����, ����� ��� �������� �����������.


					-------------------------
					|	a	|	b	| ----	|
					-------------------------
					| true	| true	| false	|
					-------------------------
					| true	| false	| true	|
					-------------------------
					| false	| true	| true	|
					-------------------------
					| false	| false	| false	|
					-------------------------
*/

int main()
{
	bool a = true;		// 1
	bool b = false;		// 0

	bool result = (a || b) && !(a && b);	// 1 - true	

	cout << boolalpha << result << endl;

	return 0;
}