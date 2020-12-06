#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	
	setlocale(LC_CTYPE, "rus");

	string str = "Угадайте загаданный цвет с 5-ти попыток.";

	int maxAttempt = 5;		// Допустимое количество попыток
	int attempt = 0;		// Номер текущей попытки
	string color = "red";	// Задуманый цвет

	while (attempt < maxAttempt) {
		attempt++;
		cout << str << " Попытка " << attempt << endl;
		string value = "";
		cin >> value;

		if (value == "") 
		{
			break;
		}
		if (value != color)
		{
			str = "Вы не угадали!";
			continue;
		}

		cout << "Поздравляем, Вы угадали с " << attempt << " попытки!" << endl;
		break;
	}
	
	system("pause");
	return 0;
}
