#include "stdafx.h"
#include <iostream>

using namespace std;
/*
	���������� � ��� ���������� ��������, �������� � ������������ ������ ���� ������� ������������� ��������� ������������, 
	���������� �������� ������ �����, ����� ��� �������� ������������ �������. �������� ���������� �� ������ ����������
	������ � ����� �Ȼ. 

					-------------------------
					|	a	|	b	|	&&	|
					-------------------------
					| true	| true	| true	|
					-------------------------
					| true	| false	| false	|
					-------------------------
					| false	| true	| false	|
					-------------------------
					| false	| false	| false	|
					-------------------------
*/

int main()
{
	bool a = true;		// 1
	bool b = true;		// 0

	bool result = a && b;

	cout << boolalpha << result << endl;

    return 0;
}

//#include "stdafx.h"
//#include <iostream>
//
//using namespace std;
//
//int main()
//{
//
//
//	return 0;
//}