#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{

	int counter = 0;

Label:

	counter++;
	cout << "Counter = " << counter << endl;

	if (counter < 3)
	{
		goto Label;
	}

	cout << "End";

	cin.get();
	return 0;
}
