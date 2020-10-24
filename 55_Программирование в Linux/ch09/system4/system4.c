#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (void)
{
	int result = system ("ls");
	printf ("result: %d\n", WEXITSTATUS (result));
	result = system ("ls abrakadabra");
	printf ("result: %d\n", WEXITSTATUS (result));
	result = system ("abrakadabra");
	printf ("result: %d\n", WEXITSTATUS (result));
	return 0;
}
