#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
    // функция setlocale задает локаль, которая будет использоваться текущей программой
    setlocale(LC_ALL, "rus");       // LC_ALL - вся локаль, второй параметр - строка, содержащая имя локали.

	int a = 3, b = 2;

	if (a < b)
	{
		cout << "a < b" << endl;
	}

	cout << "Эта строка выполнится всегда!";

	cin.get();
    return 0;
}

