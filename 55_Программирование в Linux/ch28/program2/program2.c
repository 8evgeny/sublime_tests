#include <stdio.h>

void change_a (int * mya)
{
	*mya += 10;
}

int main (int argc, char ** argv)
{
	int a;

	if (argc < 2) {
		fprintf (stderr, "Too few arguments\n");
		return 1;
	}
	
	a = 15;

	change_a (&a);

	printf ("Number: %d\n", a);
	return atoi (argv[1]);
}
