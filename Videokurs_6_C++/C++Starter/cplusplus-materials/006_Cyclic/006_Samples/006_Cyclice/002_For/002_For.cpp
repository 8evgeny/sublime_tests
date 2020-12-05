#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
	int count = 0;

	for (int i = 5; i > count; i--)
	{
		cout << "Count " << i << endl;
	}
	cout << "This line is always executed";

	cin.get();
	return 0;
}