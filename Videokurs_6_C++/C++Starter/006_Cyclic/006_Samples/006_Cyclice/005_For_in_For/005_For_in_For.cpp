#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	for (int i = 0; i < 5; i++)
	{
		// ������� ���� ������� �� 5 ���������
		for (int j = 0; j < 5; j++)
		{
			cout << "* ";
		}
		// ������� �� ����� ������
		cout << endl;
	}
	
	cin.get();
	return 0;
}
