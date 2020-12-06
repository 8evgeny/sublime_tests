#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");

	int lines = 15;			// Количество строк
	int symbInLines = 30;	// Количество символов в строке
	char symbol = '*';		// Символ 

	for (int i = 1; i <= lines; i++)
	{
		if (i == 1 || i == lines) // 1-я и последняя строка
		{
			for (int j = 1; j <= symbInLines; j++)
			{
				cout << symbol; // сплошная из символов
			}
		}
		else // все строки между первой и заключительной
		{
			cout << symbol; // показать один символ
			for (int j = 1; j <= symbInLines - 2; j++)
			{
				cout << ' '; // пробелы в строке (symbInLines - 2) раз
			}
			cout << symbol; // показать ещё один символ
		}
		cout << endl; // новая строка
	}

	cout << endl;

	system("pause");
	return 0;
}
