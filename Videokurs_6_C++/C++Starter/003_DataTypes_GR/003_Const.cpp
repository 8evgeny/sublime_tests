//  константа - область памяти, в которой хранится значение, которое нельзя изменить

//#include "stdafx.h"
#include <iostream>
#include <climits>
using namespace std;

int main()
{	
    // на 11-й строке мы создаем константу типа int с именем Month и присваиваем ей значение 12
	const int MONTH = 12;

    // значение константы изменять запрещенно
	// MONTH = 15;

	// const int a;
	// a = 10;

	int c = INT_MAX;

	cout << "INT_MAX = " << c << endl;

    return 0;
}

