#include "stdafx.h"
#include <iostream>>

using namespace std;

int main()
{
	// В теле функции main, на 9-й строке, вызываем функцию TestFunction
	TestFunction();		// ошибка времени выполнения, компилятор не знает о существовании функции TestFunction

	system("pause");
	return 0;
}

// На 17-й строке создаем функцию с именем TestFunction, которая ничего не принимает и не возвращает
// В теле функции выводим строку в консоль
void TestFunction()
{
	cout << "Hello, I'm  your first function!" << endl;
}

