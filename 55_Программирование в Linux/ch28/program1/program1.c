#include <stdio.h>

void change_a (int * mya)
{
	*mya += 10;
}

int main (void)
{
	int a;
	a = 15;

	change_a (&a);

	printf ("Number: %d\n", a);
	return 0;
}
