#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{

	cout << "Start program!" << endl;

	goto label;
	
	cout << "Some instruction..." << endl;

label: 
	cout << "End program!" << endl;

	cin.get();
	return 0;
}
