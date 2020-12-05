//  онстанта - область пам€ти, в которой хранитс€ значение, которое нельз€ изменить

#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{	
	// Ќа 11-й строке мы создаем константу типа int с именем Month и присваиваем ей значение 12
	const int MONTH = 12;

	// «начение константы измен€ть запрещенно
	// MONTH = 15;

	// const int a;
	// a = 10;

	int c = INT_MAX;

	cout << "INT_MAX = " << c << endl;

	// «адержка
	cin.get();
    return 0;
}

