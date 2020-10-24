#include <stdio.h>
#include <dirent.h>

void read_directory (DIR * dir) 
{
	struct dirent * entry;
	while ((entry = readdir (dir)) != NULL)
		printf ("%s\n", entry->d_name);
}

int main (int argc, char ** argv)
{
	DIR * dir;
	
	if (argc < 2) {
		fprintf (stderr, "Too few arguments\n");
		return 1;
	}
	
	dir = opendir (argv[1]);
	if (dir == NULL) {
		fprintf (stderr, "opendir() error\n");
		return 1;
	}

	read_directory (dir);	
	
	printf ("-- RE-READ --\n");

	rewinddir (dir);
	read_directory (dir);	

	closedir (dir);
	return 0;
}
