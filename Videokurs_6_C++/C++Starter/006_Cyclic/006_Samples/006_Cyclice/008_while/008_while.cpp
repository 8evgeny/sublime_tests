#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int count = 5;


	while (count > 0)
	{
		cout << "Count = " << count << endl;
		count--;

		break;	// ���  ��������� ��������� ������ �����, � ������� ���������� ���������� ����������� ����� ����������� ������ ����� 
	
		cout << "This line is never executed";
	}

	cout << "This line is always executed";

	cin.get();
	return 0;
}
