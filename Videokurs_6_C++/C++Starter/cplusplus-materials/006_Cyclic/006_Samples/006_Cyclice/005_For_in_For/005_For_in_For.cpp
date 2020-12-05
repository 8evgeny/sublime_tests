#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	for (int i = 0; i < 5; i++)
	{
		// Выводим одну строчку из 5 звездочек
		for (int j = 0; j < 5; j++)
		{
			cout << "* ";
		}
		// Переход на новую строку
		cout << endl;
	}
	
	cin.get();
	return 0;
}
