#include <unistd.h>
#include <stdio.h>

int main (void)
{
	if (nice (5) == -1) {
		fprintf (stderr, "Nice error\n");
		return 1;
	}

	execlp ("bash", "bash", NULL);
	fprintf (stderr, "Exec error\n");
	return 0;
}
