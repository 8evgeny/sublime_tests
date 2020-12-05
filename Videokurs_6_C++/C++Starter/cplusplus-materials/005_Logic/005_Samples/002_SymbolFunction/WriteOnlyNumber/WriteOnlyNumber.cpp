
#include "stdafx.h"
#include <iostream>

using namespace std;


int main()
{
	char number;

	while (true)
	{
		cout << "Enter the digit symbol" << endl;
		cin >> number;

		if (isdigit(number)) {
			cout << "User entered the number - " << number << endl;
			continue;
		}
		cout << "The " << number << " is not a digit! Try again!" << endl;
	}



    return 0;
}

