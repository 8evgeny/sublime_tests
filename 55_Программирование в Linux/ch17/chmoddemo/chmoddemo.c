#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

#define ANSWER_SIZE 256

void add_mode (mode_t * mode, const char * answer, mode_t bit)
{
	if (answer[0] == 'y') {
		*mode |= bit;
		printf ("set\n");
	} else {
		printf ("not set\n");
	}
}

int main (int argc, char ** argv)
{
	char * answer;
	mode_t mode = 0000;
	
	if (argc < 2) {
		fprintf (stderr, "Too few arguments\n");
		return 1;
	}

	answer = (char *) malloc (sizeof (char) *
			ANSWER_SIZE);
	if (answer == NULL) {
		fprintf (stderr, "malloc() error\n");
		return 1;
	}
	
	printf ("User can read: ");
	scanf ("%s", answer);
	add_mode (&mode, answer, S_IRUSR);

	printf ("User can write: ");
	scanf ("%s", answer);
	add_mode (&mode, answer, S_IWUSR);

	printf ("User can execute: ");
	scanf ("%s", answer);
	add_mode (&mode, answer, S_IXUSR);
	
	printf ("Group can read: ");
	scanf ("%s", answer);
	add_mode (&mode, answer, S_IRGRP);

	printf ("Group can write: ");
	scanf ("%s", answer);
	add_mode (&mode, answer, S_IWGRP);

	printf ("Group can execute: ");
	scanf ("%s", answer);
	add_mode (&mode, answer, S_IXGRP);

	printf ("World can read: ");
	scanf ("%s", answer);
	add_mode (&mode, answer, S_IROTH);

	printf ("World can write: ");
	scanf ("%s", answer);
	add_mode (&mode, answer, S_IWOTH);

	printf ("World can execute: ");
	scanf ("%s", answer);
	add_mode (&mode, answer, S_IXOTH);

	printf ("SUID: ");
	scanf ("%s", answer);
	add_mode (&mode, answer, S_ISUID);

	printf ("SGID: ");
	scanf ("%s", answer);
	add_mode (&mode, answer, S_ISGID);

	printf ("Sticky: ");
	scanf ("%s", answer);
	add_mode (&mode, answer, S_ISVTX); 

	if (chmod (argv[1], mode) == -1) {
		fprintf (stderr, "chmod() error\n");
		return 1;
	}

	free (answer);
	return 0;
}
