#include "stdafx.h"
#include <iostream>

// Директива using - импортирует пространство имен, избавляя от необхожимости использования оператор разрешения контекста
//using namespace std;


// Объявление using - импортирует только указанные составляющие пространства имен
using std::cout;
using std::endl;

int main()
{
	cout << "Hello world" << endl;

	return 0;
}

