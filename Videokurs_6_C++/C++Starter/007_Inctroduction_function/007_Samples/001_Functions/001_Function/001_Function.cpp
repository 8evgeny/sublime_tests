#include "stdafx.h"
#include <iostream>>

using namespace std;

// На 8-й строке создаем функцию с именем TestFunction, которая ничего не принимает и не возвращает
// В теле функции выводим строку в консоль
void TestFunction()
{
	cout << "Hello, I'm  your first function!" << endl;
}

int main()
{
	// В теле функции main, на 16-й строке, вызываем функцию TestFunction
	TestFunction();

	system("pause");
    return 0;
}

