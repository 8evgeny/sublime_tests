#include "stdafx.h"
#include <iostream>

using namespace std;

// Анонимное (безымянное) пространство имен
namespace {
	int a = 10;
}

int main()
{
	cout << "Variable a from namespace withput name = " << a << endl;
	return 0;
}