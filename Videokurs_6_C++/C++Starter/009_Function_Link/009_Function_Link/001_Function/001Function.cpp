#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

// Перегруженные функции могут отличаться типом и количеством аргументов
void Function();
void Function(string s);
void Function(int i);
void Function(double d);
void Function(string s, int i);
void Function(int i, string s);

// void Function(string); // Так делать нельзя

int main()
{
	Function();                  // 1-я перегрузка.
	Function("A");               // 2-я перегрузка.
	Function(1);                 // 3-я перегрузка.
	Function(3.14);              // 4-я перегрузка.
	Function("B ", 2);           // 5-я перегрузка.
	Function(3, " C");           // 6-я перегрузка.

	system("pause");
    return 0;
}

void Function()
{
	cout << "Hello" << endl;
}

void Function(string s)
{
	cout << s << endl;
}

void Function(int i)
{
	cout << i << endl;
}

void Function(double d)
{
	cout << d << endl;
}

void Function(string s, int i)
{
	cout << "s = " << s << ", i = " << i << endl;
}

void Function(int i, string s)
{
	cout << "i = " << i << ", s = " << s << endl;
}