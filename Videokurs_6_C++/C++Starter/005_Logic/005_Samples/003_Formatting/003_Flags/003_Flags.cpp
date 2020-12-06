#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{

	cout.setf(ios::boolalpha);						// ¬ключить вывод логических величин в текстовом виде

	bool a = true;
	bool b = false;

	cout << "a = " << a << "; b = " << b << endl;

	cout.unsetf(ios::boolalpha /* noboolalpha */);	// ќтключить вывод логических величин в текстовом виде
	
	
	cout.unsetf(ios::dec);
	cout.setf(ios::showbase /* noshowbase */ | ios::showpos /* noshowpos */);

	int number = 16;

	cout << "number = " << number << endl;

    return 0;
}

