#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int count = 5;

	for (int i = 0; i < count; i++)
	{
		cout << "Iteration " << i << endl;

		break;	// Эта  инстукция остановит работу цикла, и предаст управление инструкцие находящейся после операторных скобок цикла 

		cout << "This line is never executed";
	}

	cout << "This line is always executed";

	cin.get();	
	return 0;
}
