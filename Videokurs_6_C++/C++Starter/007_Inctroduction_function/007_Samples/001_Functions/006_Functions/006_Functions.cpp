#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

string Function(string);

int main()
{
	string sentence = Function("Vladimir");

	cout << sentence << endl;

	system("pause");
	return 0;
}

string Function(string name) 
{
	string hi = "Hello, " + name + "!";

	return hi;
}