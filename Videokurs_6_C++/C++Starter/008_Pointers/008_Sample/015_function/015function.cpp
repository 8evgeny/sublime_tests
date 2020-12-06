#include "stdafx.h"
#include <iostream>

#define SIZE 10

void push(int i);
int pop(void);

int *top_s, *p1, stack[SIZE];

using namespace std;

int main()
{
	int value;

	top_s = stack;
	p1 = stack;

	do {
		cout << "Enter the number: " << endl;
		cin >> value;

		if (value != 0) {
			push(value);
		}
		else
		{
			cout << "The number on stack top equal " << pop() << endl;
		}

	} while (value != -1);


	system("pause");
	return 0;
}

void push(int i) 
{
	p1++;
	if (p1 == (top_s + SIZE)) {
		cout << "The stack is overflow" << endl;;
		exit(1);
	}
	*p1 = i;
}

int pop(void)
{
	if (p1 == top_s)
	{
		cout << "Stack is empty!" << endl;
		exit(1);
	}
	p1--;
	return *(p1 + 1);
}

