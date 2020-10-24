#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc, char ** argv)
{
       int fd;
       if (argc < 2) {
              fprintf (stderr, "Too few arguments\n");
              return 1;
       }

       fd = open (argv[1], O_WRONLY | O_CREAT | O_EXCL, 0644);
       if (fd == -1) {
              fprintf (stderr, "Cannot create file (%s)\n",
                            argv[1]);
              return 2;
       }

       if (close (fd) == -1) {
              fprintf (stderr, "Cannot close file "
                            "with descriptor=%d\n", fd);
              return 3;
       }

       if (close (fd) == -1) {
              fprintf (stderr, "Cannot close file "
                            "with descriptor=%d\n", fd);
              return 4;
       }
       return 0;
}
