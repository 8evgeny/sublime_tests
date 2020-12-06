#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	// Динамическое выделение памяти. С помощью оператора new можно выделять необходимое количество памяти.

	int *pointer = new int[3];

	// Способы заполнить динамический массив
	// 1-й
	pointer[0] = 1;
	pointer[1] = 2;
	pointer[2] = 3;

	//2-й
	*pointer = 1;
	*(pointer + 1) = 2;
	*(pointer + 2) = 3;

	cout << "Value : " << *pointer			<< "; Adress : " << pointer << endl;
	cout << "Value : " << *(pointer + 1)	<< "; Adress : " << pointer + 1 << endl;
	cout << "Value : " << *(pointer + 2)	<< "; Adress : " << pointer + 2 << endl;


	system("pause");
	return 0;
}

