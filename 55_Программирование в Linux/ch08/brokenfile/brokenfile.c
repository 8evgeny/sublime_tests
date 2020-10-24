#include <stdio.h>
#include <fcntl.h>

int main (int argc, char ** argv)
{
       int fd;
       FILE * filep;
       if (argc < 2) {
              fprintf (stderr, "Too few arguments\n");
              return 1;
       }

       fd = open (argv[1], O_RDONLY);
       if (fd == -1) {
              fprintf (stderr, "Cannot open file "
                            "(%s)\n", argv[1]);
              return 2;
       }

       filep = fdopen (fd, "w");
       if (filep == NULL) {
              fprintf (stderr, "Cannot create file pointer\n");
              return 3;
       }

       close (fd);
       return 0;
}
