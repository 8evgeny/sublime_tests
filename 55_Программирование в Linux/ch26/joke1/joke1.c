#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main (void)
{
	int fd = creat ("--version", 0640);
	if (fd == -1) {
		fprintf (stderr, "creat() error\n");
		return 1;
	}

	close (fd);
	return 0;
}
