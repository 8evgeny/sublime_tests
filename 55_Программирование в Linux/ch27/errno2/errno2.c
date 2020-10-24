#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main (int argc, char ** argv)
{
	int fd, errno_local;
	
	if (argc < 2) {
		fprintf (stderr, "Too few arguments\n");
		return 1;
	}

	fd = open (argv[1], O_RDWR, 0600);
	if (fd == -1) {
		fprintf (stderr, "%s\n", strerror (errno));
		return 1;
	}

	close (fd);
	return 0;
}
