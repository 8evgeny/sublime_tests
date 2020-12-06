#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int count = 5;

	do
	{
		cout << "Count " << count << endl;
		count--;
		
		break;	// Эта инструкция прерывает работу цикла 

		cout << "This line is never executed";	// Эта строка не выполнится никогда
	} while (count > 0);

	cout << "This line is always executed" << endl;

	cin.get();
	return 0;
}
